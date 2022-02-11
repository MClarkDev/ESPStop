#include "Status.h"

Status::Status() {
  appState = AppState::Booting;

  xTaskCreatePinnedToCore(StatusTask, "StatusTask", 2048, (void*) this, 1, NULL, 1);
}

void Status::setAppState(AppState state) {
  this->appState = state;
}

AppState Status::getAppState() {
  return appState;
}

void StatusTask(void *parameter) {
  Status* stat = ((Status*) parameter);

  CRGB leds[NUM_LEDS];
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  while (true) {

    FastLED.show();
    vTaskDelay(100);

    switch (stat->getAppState()) {

      case AppState::Booting:
        leds[0] = CRGB::Black;
        leds[1] = CRGB::Black;
        leds[2] = CRGB::White;
        leds[3] = CRGB::Black;
        leds[4] = CRGB::Black;
        break;

      case AppState::Setup:
        leds[0] = CRGB::Black;
        leds[1] = CRGB::Black;
        leds[2] = CRGB::Blue;
        leds[3] = CRGB::Black;
        leds[4] = CRGB::Black;
        break;

      case AppState::Connecting:
        leds[0] = CRGB::Black;
        leds[1] = CRGB::Black;
        leds[2] = CRGB::Purple;
        leds[3] = CRGB::Black;
        leds[4] = CRGB::Black;
        break;

      case AppState::Armed:
        leds[0] = CRGB::Orange;
        leds[1] = CRGB::Orange;
        leds[2] = CRGB::Red;
        leds[3] = CRGB::Orange;
        leds[4] = CRGB::Orange;
        break;

      case AppState::Active:
        leds[0] = CRGB::Black;
        leds[1] = CRGB::Black;
        leds[2] = CRGB::Green;
        leds[3] = CRGB::Black;
        leds[4] = CRGB::Black;
        break;

      case AppState::Stopped:
        leds[0] = CRGB::Red;
        leds[1] = CRGB::Red;
        leds[2] = CRGB::Red;
        leds[3] = CRGB::Red;
        leds[4] = CRGB::Red;
        break;
    }
  }
}
