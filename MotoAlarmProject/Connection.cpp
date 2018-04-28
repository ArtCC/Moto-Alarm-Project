// Import classes and libraries
#include "ImportClasses.h"

// Public util functions
bool getStatusCorrectConnection() {

  if (client.connect(server, port)) {

    return true;
  } else {

    if (isDebug()) {

      Serial.println("getStatusCorrectConnection: Connection failed");
    }

    client.stop();

    return false;
  }
}
