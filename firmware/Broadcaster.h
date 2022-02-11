#ifndef Broadcaster_H
#define Broadcaster_H

#include <Arduino.h>

#include <BleepingLibrary.h>

#include <WiFiUdp.h>

#include "AppState.h"

class Broadcaster {
  private:
    boolean running;
    AppState appState;
    BleepingLibrary* bLib;

  public:
    Broadcaster();
    boolean isConnected();
    boolean isRunning();
    void setAppState(AppState state);
    AppState getAppState();
    String getCastAddress();
    int getCastPort();
};

void BroadcasterTask(void *parameter);

#endif
