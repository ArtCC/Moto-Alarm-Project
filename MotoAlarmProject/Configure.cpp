// Import classes and libraries
#include "ImportClasses.h"

void configureServices() {
  Serial.begin(115200);

  activateBluetoothModule();
}

void startSubscribeServices() {
  subscribeToEventsBluetoothModule();
}
