#ifndef ESPStop_H
#define ESPStop_H

#include <Arduino.h>

#include "Status.h"
#include "Safety.h"
#include "Broadcaster.h"

class ESPStop {
  private:
    Status* stat;
    Safety* safe;
    Broadcaster* bcast;

  public:
    ESPStop();
    void setup();
    void loop();
};

#endif
