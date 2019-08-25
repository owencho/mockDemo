#include "unity.h"
#include "mock_Heater.h"
#include "HeaterController.h"
#include "Type.h"

void setUp(void){}
void tearDown(void){}

void test_heaterController_init_to_heating_state(void){
    HeaterSwitch powerSwitch = ON;
    HeaterState state;
    state = INIT_STATE;
    heaterTurn_Expect(powerSwitch);
    heaterController(&state);
    TEST_ASSERT_EQUAL(HEATING_STATE, state);
}

void test_heaterController_idle_to_stable_state(void){
    HeaterSwitch powerSwitch = ON;
    HeaterState state;
    state = IDLE_STATE;
    readTemperature_ExpectAndReturn(71.3);
    heaterTurn_Expect(powerSwitch);
    heaterController(&state);
    TEST_ASSERT_EQUAL(STABLE_STATE, state);
}

void test_heaterController_remain_idle_state(void){
    HeaterState state;
    state = IDLE_STATE;
    readTemperature_ExpectAndReturn(100.2);
    heaterController(&state);
    TEST_ASSERT_EQUAL(IDLE_STATE, state);
}

void test_heaterController_idle_to_heating_state(void){
    HeaterSwitch powerSwitch = ON;
    HeaterState state;
    state = IDLE_STATE;
    readTemperature_ExpectAndReturn(30);
    heaterTurn_Expect(powerSwitch);
    heaterController(&state);
    TEST_ASSERT_EQUAL(HEATING_STATE, state);
}

void test_heaterController_heating_to_stable_state(void){
    HeaterState state;
    state = HEATING_STATE;
    readTemperature_ExpectAndReturn(60.1);
    heaterController(&state);
    TEST_ASSERT_EQUAL(STABLE_STATE, state);
}

void test_heaterController_heating_to_idle_state(void){
    HeaterSwitch powerSwitch = OFF;
    HeaterState state;
    state = HEATING_STATE;
    readTemperature_ExpectAndReturn(100.3);
    heaterTurn_Expect(powerSwitch);
    heaterController(&state);
    TEST_ASSERT_EQUAL(IDLE_STATE, state);
}

void test_heaterController_remain_heating_state(void){
    HeaterState state;
    state = HEATING_STATE;
    readTemperature_ExpectAndReturn(31);
    heaterController(&state);
    TEST_ASSERT_EQUAL(HEATING_STATE, state);
}

void test_heaterController_stable_to_idle_state(void){
    HeaterState state;
    state = STABLE_STATE;
    HeaterSwitch powerSwitch = OFF;
    readTemperature_ExpectAndReturn(91.3);
    heaterTurn_Expect(powerSwitch);
    heaterController(&state);
    TEST_ASSERT_EQUAL(IDLE_STATE, state);
}

void test_heaterController_remain_stable_state(void){
    HeaterState state;
    state = STABLE_STATE;
    readTemperature_ExpectAndReturn(69.71);
    heaterController(&state);
    TEST_ASSERT_EQUAL(STABLE_STATE, state);
}

void test_heaterController_stable_to_heating_state(void){
    HeaterState state;
    state = STABLE_STATE;
    readTemperature_ExpectAndReturn(32.1);
    heaterController(&state);
    TEST_ASSERT_EQUAL(HEATING_STATE, state);
}
