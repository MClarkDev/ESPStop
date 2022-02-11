#ifndef Broadcaster_H
#define Broadcaster_H

#include <Arduino.h>

#include <BleepingLibrary.h>

#include <WiFiUdp.h>

#include "AppState.h"

class Broadcaster {
  private:
    boolean configured;
    AppState appState;
    BleepingLibrary* bLib;

  public:
    Broadcaster();
    boolean isConnected();
    boolean isConfigured();
    void setAppState(AppState state);
    AppState getAppState();
    String getCastAddress();
};

void BroadcasterTask(void *parameter);

#endif
