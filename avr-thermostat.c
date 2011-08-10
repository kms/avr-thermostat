/* avr-thermostat
 * ...
 *
 * (c) Karl-Martin Skontorp <kms@skontorp.net>
 * Licensed under the GNU GPL 2.0 or later.
 */

#define F_CPU 600000UL

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hysteresis.h"

enum thresholdPort {
    LOW_PORT,
    HIGH_PORT
};

int16_t measureTemperature(void) {
    ADMUX = _BV(MUX0); // PB2 / ADC1

    ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS1) | _BV(ADPS0);
    loop_until_bit_is_set(ADCSRA, ADIF);
    ADCSRA |= _BV(ADIF);
    ADCSRA &= ~(_BV(ADEN));

    int16_t temp;
    temp = ADCL | (ADCH << 8);
    temp *= 0.49;
    temp -= 273;

    return temp;
}

int16_t measureThreshold(enum thresholdPort thresholdPort) {
    switch (thresholdPort) {
        case LOW_PORT:
            ADMUX = _BV(MUX0) | _BV(MUX1); // PB3 / ADC3
            break;
        case HIGH_PORT:
            ADMUX = _BV(MUX1); // PB4 / ADC2
            break;
    }

    ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS1) | _BV(ADPS0);
    loop_until_bit_is_set(ADCSRA, ADIF);
    ADCSRA |= _BV(ADIF);
    ADCSRA &= ~(_BV(ADEN));

    int16_t threshold;
    threshold = ADCL | (ADCH << 8);
    threshold *= 0.098;

    return threshold;
}

int main(void) {
    /* Watchdog */
    wdt_reset();
    //wdt_enable(WDTO_1S);
    wdt_disable();

    /* Ports */
    PORTB = 0xff;
    DDRB = _BV(PINB0);

    /* Power saving */
    ACSR = _BV(ACD);

    hysteresis h;
    initHysteresis(&h);

    PORTB |= _BV(PINB0);
    _delay_ms(5000);
    PORTB &= ~(_BV(PINB0));

    for (;;) {
        wdt_reset();

        setThresholds(&h, measureThreshold(LOW_PORT),
                measureThreshold(HIGH_PORT));
   
        updateHysteresis(&h, measureTemperature());

        if (h.currentState == HIGH) {
            PORTB |= _BV(PINB0);
        } else if (h.currentState == LOW) {
            PORTB &= ~(_BV(PINB0));
        }

        _delay_ms(100);
    }

    return 0;
}
