/* avr-thermostat
 * ...
 *
 * (c) Karl-Martin Skontorp <kms@skontorp.net>
 * Licensed under the GNU GPL 2.0 or later.
 */

#ifndef HYSTERESIS_H
#define HYSTERESIS_H

enum hysteresisState {
    HIGH,
    LOW
};

struct hysteresis {
    uint8_t toHighThreshold;
    uint8_t toLowThreshold;
    enum hysteresisState currentState;
};

void initHysteresis(hysteresis *h, uint8_t low, uint8_t high);
void updateHysteresis(hysteresis *h, uint8_t newValue);

#endif
