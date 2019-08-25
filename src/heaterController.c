#include "heaterController.h"
#include "unity.h"

void heaterController(HeaterState * state){
    float a;
    int sw;
    sw = *state;
    switch (sw) {
        case INIT_STATE: heaterTurn(ON);
                        *state = HEATING_STATE;
                        break;
        case IDLE_STATE:
                        a = readTemperature();
                        if(a > 90 ){
                          *state = IDLE_STATE;
                        }
                        else if(a >= 60 && a < 90){
                          heaterTurn(ON);
                          *state = STABLE_STATE;
                        }
                        else{
                          heaterTurn(ON);
                          *state = HEATING_STATE;
                        }
                        break;
        case STABLE_STATE:
                        a = readTemperature();
                        if(a > 90 ){
                          heaterTurn(OFF);
                          *state = IDLE_STATE;
                        }
                        else if(a >= 60 && a < 90){
                          *state = STABLE_STATE;
                        }
                        else{
                          *state = HEATING_STATE;
                        }
                        break;
        case HEATING_STATE:
                       a = readTemperature();
                       if(a > 90 ){
                         heaterTurn(OFF);
                          *state = IDLE_STATE;
                       }
                       else if(a >= 60 && a < 90){
                         *state = STABLE_STATE;
                       }
                       else{
                         *state = HEATING_STATE;
                       }
                       break;
        default:
                        *state = INIT_STATE;
                        break;
    }
}
