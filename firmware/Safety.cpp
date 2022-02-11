#include "Safety.h"

Safety::Safety() {

  pinMode(14, INPUT_PULLDOWN);
  pinMode(27, INPUT_PULLDOWN);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  pinMode(26, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  safetyState = SafetyState::Stopped;

  xTaskCreatePinnedToCore(SafetyTask, "SafetyTask", 2048, (void*) this, 2, NULL, 1);
}

SafetyState Safety::getSafetyState() {
  return safetyState;
}

void Safety::setSafetyState(SafetyState state) {
  this->safetyState = state;
}

void SafetyTask(void *parameter) {
  Safety* safe = ((Safety*) parameter);

  while (true) {
    vTaskDelay(10);

    boolean _14 = digitalRead(14);
    boolean _27 = digitalRead(27);

    boolean stopped = _14 || !_27;

    if (stopped) {
      safe->setSafetyState(SafetyState::Stopped);
      continue;
    }

    if (safe->getSafetyState() == SafetyState::Stopped) {
      safe->setSafetyState(SafetyState::Armed);
      continue;
    }

    if (!digitalRead(26)) {
      safe->setSafetyState(SafetyState::Active);
      continue;
    }
  }
}
