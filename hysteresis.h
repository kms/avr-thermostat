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

typedef struct {
    int16_t toHighThreshold;
    int16_t toLowThreshold;
    enum hysteresisState currentState;
} hysteresis;

void initHysteresis(hysteresis *h);
void updateHysteresis(hysteresis *h, int16_t newValue);
void setThresholds(hysteresis *h, int16_t low, int16_t high);

#endif
