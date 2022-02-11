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
  boolean configured = bLib->isConfigured();
  if (!configured || forceSetup) {

    BleepingServer* server = bLib->getServer();
    server->startServer();

    // Custom Config Parameters
    server->startCustomPropertyService(uuids, 2);

    running = false;
    return;
  }

  // Load WiFi connection properties from bleeping config
  String netName = bLib->getString(BleepingProperty::NetworkName);
  String netPass = bLib->getString(BleepingProperty::NetworkPassword);

  ESP_LOGI(_BLib, "Connecting to: %s", netName.c_str());

  running = true;
  WiFi.mode(WIFI_STA);
  WiFi.begin(netName.c_str(), netPass.c_str());

  xTaskCreatePinnedToCore(BroadcasterTask, "BroadcasterTask", 2048, (void*) this, 1, NULL, 1);
}

boolean Broadcaster::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

boolean Broadcaster::isRunning() {
  return running;
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

int Broadcaster::getCastPort() {
  return atoi(bLib->getConfig()->getString(ConfUUID_BCastPort).c_str());
}

void BroadcasterTask(void *parameter) {
  Broadcaster* bcast = ((Broadcaster*) parameter);

  WiFiUDP udp;
  String bcastHost = bcast->getCastAddress();
  int bcastPort = bcast->getCastPort();

  while (true) {
    vTaskDelay(500);
    if (!bcast->isConnected()) {
      continue;
    }

    const char* msg;
    udp.beginPacket(bcastHost.c_str() , bcastPort);
    switch (bcast->getAppState()) {
      case AppState::Active:
        msg = "OK";
        break;
      case AppState::Armed:
        msg = "ARM";
        break;
      case AppState::Stopped:
        msg = "STOP";
        break;
      default:
        msg = "ERR";
        break;
    }

    udp.printf("%s", msg);
    udp.endPacket();
  }
}
