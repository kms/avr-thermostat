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
    h.currentState = HIGH;

    initHysteresis(&h, 50, 100);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueNotCrossingThresholds) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 10);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueHittingToLowThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 50);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValuePassingToLowThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 51);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueHittingToHighThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 100);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValuePassingToHighThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 101);
    ASSERT_EQ(HIGH, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateInHighWithValuePassingToHighThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 101);
    updateHysteresis(&h, 99);
    ASSERT_EQ(HIGH, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateInHighWithValueHittingToLowThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 101);
    updateHysteresis(&h, 50);
    ASSERT_EQ(HIGH, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateInHighWithValuePassingToLowThreshold) {
    hysteresis h;

    initHysteresis(&h, 50, 100);
    updateHysteresis(&h, 101);
    updateHysteresis(&h, 49);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateCycleBackAndForth) {
    hysteresis h;

    initHysteresis(&h, 50, 100);

    updateHysteresis(&h, 101);
    ASSERT_EQ(HIGH, h.currentState);

    updateHysteresis(&h, 49);
    ASSERT_EQ(LOW, h.currentState);

    updateHysteresis(&h, 101);
    ASSERT_EQ(HIGH, h.currentState);

    updateHysteresis(&h, 51);
    ASSERT_EQ(HIGH, h.currentState);

    updateHysteresis(&h, 49);
    ASSERT_EQ(LOW, h.currentState);

    updateHysteresis(&h, 48);
    ASSERT_EQ(LOW, h.currentState);
}
