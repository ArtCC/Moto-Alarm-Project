// Import classes and libraries
#include "ImportClasses.h"

// Variables
// "Multi-thread" with millis()
unsigned long intervalOTAUpdate = 604800000;
unsigned long previousMillisOTAUpdate = 0;

// Public functions
void beginModuleForUpdate() {
  OTAUpdate.begin(server, portForUpdate, folderForUpdate);
}

void checkIfExistUpdateInServer() {
  unsigned long currentMillisOTAUpdate = millis();

  if ((unsigned long)(currentMillisOTAUpdate - previousMillisOTAUpdate) >= intervalOTAUpdate) {

    if (OTAUpdate.checkUpdate()) {

      OTAUpdate.startUpdate();
    }

    previousMillisOTAUpdate = millis();
  }
}
