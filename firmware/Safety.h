#ifndef Safety_H
#define Safety_H

#include <Arduino.h>

enum class SafetyState {
  Armed,
  Active,
  Stopped
};

class Safety {
  private:
    SafetyState safetyState;

  public:
    Safety();
    SafetyState getSafetyState();
    void setSafetyState(SafetyState state);

};

void SafetyTask(void *parameter);

#endif
