/* avr-thermostat
 * ...
 *
 * (c) Karl-Martin Skontorp <kms@skontorp.net>
 * Licensed under the GNU GPL 2.0 or later.
 */

#include <stdint.h>

#include "hysteresis.h"

void initHysteresis(hysteresis *h, uint8_t low, uint8_t high) {
    h->currentValue = 0;

    if (h->currentValue < high) {
        h->currentState = LOW;
    } else {
        h->currentState = HIGH;
    }
}

void updateHysteresis(hysteresis *h, uint8_t newValue) {
    h->currentValue = newValue;
}
