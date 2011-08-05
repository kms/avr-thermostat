/* avr-thermostat
 * ...
 *
 * (c) Karl-Martin Skontorp <kms@skontorp.net>
 * Licensed under the GNU GPL 2.0 or later.
 */

#include <stdint.h>
#include <math.h>
#include "gtest/gtest.h"

#include "hysteresis.h"

class HysteresisTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(HysteresisTest, TestInit) {
    hysteresis h;
    h.currentValue = 123;
    h.currentState = HIGH;

    initHysteresis(&h, 50, 100);
    ASSERT_EQ(0, h.currentValue);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueNotCrossingThresholds) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    ASSERT_EQ(0, h.currentValue);
    updateHysteresis(&h, 10);
    ASSERT_EQ(10, h.currentValue);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueHittingLowThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 50);
    ASSERT_EQ(LOW, h.currentState);
}