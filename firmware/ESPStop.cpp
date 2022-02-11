#include "ESPStop.h"

AppState appState;

ESPStop::ESPStop() {
  appState = AppState::Booting;
}

void ESPStop::setup() {

  stat = new Status();
  safe = new Safety();

  bcast = new Broadcaster();
}

void ESPStop::loop() {

  stat->setAppState(appState);
  bcast->setAppState(appState);
  delay(1);

  if(!bcast->isConfigured()) {
    appState = AppState::Setup;
    return;
  }

  if (!bcast->isConnected()) {
    appState = AppState::Connecting;
    return;
  }

  switch (safe->getSafetyState()) {
    case SafetyState::Armed:
      appState = AppState::Armed;
      break;

    case SafetyState::Active:
      appState = AppState::Active;
      break;

    case SafetyState::Stopped:
      appState = AppState::Stopped;
      break;
  }
}
