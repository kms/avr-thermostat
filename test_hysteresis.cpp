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
            initHysteresis(&h, 50, 100);
        }

        virtual void TearDown() {
        }

        hysteresis h;
};

TEST_F(HysteresisTest, TestInit) {
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueNotCrossingThresholds) {
    updateHysteresis(&h, 10);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueHittingToLowThreshold) {
    updateHysteresis(&h, 50);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValuePassingToLowThreshold) {
    updateHysteresis(&h, 51);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValueHittingToHighThreshold) {
    updateHysteresis(&h, 100);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateWithValuePassingToHighThreshold) {
    updateHysteresis(&h, 101);
    ASSERT_EQ(HIGH, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateInHighWithValuePassingToHighThreshold) {
    updateHysteresis(&h, 101);
    updateHysteresis(&h, 99);
    ASSERT_EQ(HIGH, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateInHighWithValueHittingToLowThreshold) {
    updateHysteresis(&h, 101);
    updateHysteresis(&h, 50);
    ASSERT_EQ(HIGH, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateInHighWithValuePassingToLowThreshold) {
    updateHysteresis(&h, 101);
    updateHysteresis(&h, 49);
    ASSERT_EQ(LOW, h.currentState);
}

TEST_F(HysteresisTest, TestUpdateCycleBackAndForth) {
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
