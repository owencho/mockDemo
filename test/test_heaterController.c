#include "unity.h"
#include "mock_heater.h"
#include "heaterController.h"
#include "type.h"
#include "heater.h"

void setUp(void){}
void tearDown(void){}

void test_idle_heater(void){
    HeaterSwitch powerSwitch = ON;
    HeaterState state;
    state = IDLE_STATE;
    heaterTurn_Expect(powerSwitch);
    heaterController(&state);
    TEST_ASSERT_EQUAL(HEATING_STATE, state);
}

void test_heating_heater(void){
    HeaterSwitch powerSwitch = ON;
    HeaterState state;
    state = HEATING_STATE;
    readTemperature_ExpectAndReturn(60);
    heaterController(&state);
    TEST_ASSERT_EQUAL(STABLE_STATE, state);
}

void test_stable_heater(void){
    HeaterState state;
    state = STABLE_STATE;
    HeaterSwitch powerSwitch = OFF;
    readTemperature_ExpectAndReturn(91.3);
    heaterTurn_Expect(powerSwitch);
    heaterController(&state);
    TEST_ASSERT_EQUAL(IDLE_STATE, state);
}
