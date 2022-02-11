#ifndef Status_H
#define Status_H

#include <Arduino.h>

#include <FastLED.h>

#include "AppState.h"

#define NUM_LEDS 5
#define DATA_PIN 25

class Status {
  private:
    AppState appState;
    
  public:
    Status();
    void setAppState(AppState state);
    AppState getAppState();
};

void StatusTask(void *parameter);


#endif
