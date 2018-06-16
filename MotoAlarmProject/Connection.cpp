// Import classes and libraries
#include "ImportClasses.h"

// Properties
// "Multi-thread" with millis()
unsigned long previousMillisForConnection = 0;
unsigned long intervalUpdateForConnection = 900000;

bool connectionIsActive = false;
int testCount = 0;

// Public functions
void setConnectionIsActive(const bool &value) {
  connectionIsActive = value;
}

bool getConnectionIsActive() {

  return connectionIsActive;
}

bool checkConnectionIsCorrect() {
  unsigned long currentMillisUpdateForConnection = millis();

  if (!getConnectionIsActive()) {

    if ((unsigned long)(currentMillisUpdateForConnection - previousMillisForConnection) >= intervalUpdateForConnection) {

      if (debug) {

        Serial.println("New check connection...");
      }

      previousMillisForConnection = millis();

      if (testCount == 5) {

        resetByCode();
      } else {

        testCount += 1;

        LGPRSClient clientTest;

        if (clientTest.connect(mapServer, port)) {

          if (debug) {

            Serial.println("testRequestToServer: ok");
          }

          setConnectionIsActive(true);

          clientTest.stop();

          return true;
        } else {

          if (debug) {

            Serial.println("testRequestToServer: ko!");
          }

          setConnectionIsActive(false);

          clientTest.stop();

          return false;
        }
      }
    }
  } else {

    testCount = 0;

    setConnectionIsActive(true);

    return true;
  }
}
