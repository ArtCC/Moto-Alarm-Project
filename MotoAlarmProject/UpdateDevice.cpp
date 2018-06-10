// Import classes and libraries
#include "ImportClasses.h"

// Properties
// "Multi-thread" with millis()
unsigned long intervalUpdateForOTAUpdate = 86400000;
unsigned long previousMillisForOTAUpdate = 0;

// Public functions
void configureOTAUpdate() {
  OTAUpdate.begin(mapServer_UPDATE, MAP_PORT_UPDATE, MAP_FOLDER_UPDATE);
}

void updateDevice() {
  unsigned long currentMillisUpdateForOTAUpdate = millis();

  if ((unsigned long)(currentMillisUpdateForOTAUpdate - previousMillisForOTAUpdate) >= intervalUpdateForOTAUpdate) {

    while (true) {

      if (OTAUpdate.checkUpdate()) {

        OTAUpdate.startUpdate();
      }
    }

    previousMillisForOTAUpdate = millis();
  }
}
