/* avr-thermostat
 * ...
 *
 * (c) Karl-Martin Skontorp <kms@skontorp.net>
 * Licensed under the GNU GPL 2.0 or later.
 */

#include <stdint.h>

#include "hysteresis.h"

void initHysteresis(hysteresis *h, uint8_t low, uint8_t high) {
    h->toLowThreshold = low;
    h->toHighThreshold = high;
    h->currentState = LOW;
}

void updateHysteresis(hysteresis *h, uint8_t newValue) {
    if (newValue > h->toHighThreshold) {
        h->currentState = HIGH;
    }

    if (newValue < h->toLowThreshold) {
        h->currentState = LOW;
    }
}
