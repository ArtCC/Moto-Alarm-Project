// Import classes and libraries
#include "ImportClasses.h"

// Public util functions
bool getStatusCorrectConnection() {

  if (client.connect(PING_TO_SERVER, port)) {

    if (isDebug()) {

      Serial.println("getStatusCorrectConnection: Correct connection");
    }

    return true;
  } else {

    if (isDebug()) {

      Serial.println("getStatusCorrectConnection: Connection failed");
    }

    client.stop();

    return false;
  }
}
