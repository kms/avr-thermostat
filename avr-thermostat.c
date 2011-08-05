/* avr-thermostat
 * ...
 *
 * (c) Karl-Martin Skontorp <kms@skontorp.net>
 * Licensed under the GNU GPL 2.0 or later.
 */

#define F_CPU 3686400UL

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "thermistor.h"

int main(void) {
    /* Watchdog */
    wdt_reset();
    wdt_disable();

    /* Ports */
    PORTB = 0xff;

    /* Power saving */
    ACSR = _BV(ACD);
    set_sleep_mode(SLEEP_MODE_IDLE);
    
    sei();

    for (;;) {
        sleep_mode();
    }

    return 0;
}
