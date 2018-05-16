// Import classes and libraries
#include "ImportClasses.h"

// Public util functions
bool getStatusCorrectConnection() {

  if (client.connect(PING_TO_SERVER, port)) {

    return true;
  } else {

    if (isDebug()) {

      Serial.println("getStatusCorrectConnection: Connection failed");
    }

    client.stop();

    return false;
  }
}
