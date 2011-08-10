/* avr-thermostat
 * ...
 *
 * (c) Karl-Martin Skontorp <kms@skontorp.net>
 * Licensed under the GNU GPL 2.0 or later.
 */

#include <stdint.h>
#include <stdio.h>

#include "hysteresis.h"

void initHysteresis(hysteresis *h) {
    h->currentState = LOW;
    setThresholds(h, 0, 0);
}

void setThresholds(hysteresis *h, int16_t low, int16_t high) {
    if (low <= high) {
        h->toLowThreshold = low;
        h->toHighThreshold = high;
    } else {
        h->toLowThreshold = high;
        h->toHighThreshold = low;
    }
}

void updateHysteresis(hysteresis *h, int16_t newValue) {
    if (newValue > h->toHighThreshold) {
        h->currentState = HIGH;
    } else if (newValue < h->toLowThreshold) {
        h->currentState = LOW;
    }
}
