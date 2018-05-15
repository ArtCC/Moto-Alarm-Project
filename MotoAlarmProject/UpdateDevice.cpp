// Import classes and libraries
#include "ImportClasses.h"

// Properties
// "Multi-thread" with millis()
unsigned long intervalUpdateForOTAUpdate = 86400000;
unsigned long previousMillisForOTAUpdate = 0;

// Public functions
void configureOTAUpdate() {
  OTAUpdate.begin(MAP_SERVER_UPDATE, MAP_PORT_UPDATE, MAP_FOLDER_UPDATE);
}

void updateDevice() {
  unsigned long currentMillisUpdate = millis();

  if ((unsigned long)(currentMillisUpdate - previousMillisForOTAUpdate) >= intervalUpdateForOTAUpdate) {

    while (true) {

      if (OTAUpdate.checkUpdate()) {

        OTAUpdate.startUpdate();
      }
    }

    previousMillisForOTAUpdate = millis();
  }
}
