#include "Broadcaster.h"

BleepingUUID ConfUUID_BCastHost = BleepingUUID("00000000-0000-0000-002f-a0f103000000");
BleepingUUID ConfUUID_BCastPort = BleepingUUID("00000000-0000-0000-002f-a0f203000000");
BleepingUUID uuids[] = { ConfUUID_BCastHost, ConfUUID_BCastPort };

Broadcaster::Broadcaster() {

  bLib = new BleepingLibrary();

  int boots = bLib->init();
  ESP_LOGI(_BLib, "Boots: %d", boots);

  delay(250);
  boolean forceSetup = !digitalRead(26);
  if (!bLib->isConfigured() || forceSetup) {

    BleepingServer* server = bLib->getServer();
    server->startServer();

    // Custom Config Parameters
    server->startCustomPropertyService(uuids, 2);

    configured = false;
    return;
  }

  // Load WiFi connection properties from bleeping config
  String netName = bLib->getString(BleepingProperty::NetworkName);
  String netPass = bLib->getString(BleepingProperty::NetworkPassword);

  ESP_LOGI(_BLib, "Connecting to: %s", netName.c_str());

  WiFi.mode(WIFI_STA);
  WiFi.begin(netName.c_str(), netPass.c_str());

  xTaskCreatePinnedToCore(BroadcasterTask, "BroadcasterTask", 2048, (void*) this, 1, NULL, 1);
}

boolean Broadcaster::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

boolean Broadcaster::isConfigured() {
  return configured;
}

AppState Broadcaster::getAppState() {
  return appState;
}

void Broadcaster::setAppState(AppState state) {
  appState = state;
}

String Broadcaster::getCastAddress() {
  return bLib->getConfig()->getString(ConfUUID_BCastHost);
}

void BroadcasterTask(void *parameter) {
  Broadcaster* bcast = ((Broadcaster*) parameter);

  WiFiUDP udp;
  String bcastHost = bcast->getCastAddress();

  while (true) {
    vTaskDelay(500);
    if (!bcast->isConnected()) {
      continue;
    }

    const char* stat = bcast->getAppState() == AppState::Active ? "OK" : "XX";

    udp.beginPacket(bcastHost.c_str() , 4443);
    udp.printf("%s @ %lu\n", stat, millis());
    udp.endPacket();
  }
}
