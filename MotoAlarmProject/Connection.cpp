// Import classes and libraries
#include "ImportClasses.h"

// Properties
char pingServer[] = "start.duckduckgo.com";

// Public util functions
bool getStatusCorrectConnection() {

  if (client.connect(pingServer, port)) {

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
