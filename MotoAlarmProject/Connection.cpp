// Import classes and libraries
#include "ImportClasses.h"

// Properties
// "Multi-thread" with millis()
unsigned long previousMillisForConnection = 0;
unsigned long intervalUpdateForConnection = 3600000;

bool connectionIsActive = false;
int testCount = 0;

// SMS text
String notConnectionForSMS = "Sorry... I don't have internet connection... :(";

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

        sendSMSToPhoneNumber(getUserPhone(), textForResetSMS);
        resetByCode();
      } else {

        if (testCount == 1) {

          sendSMSToPhoneNumber(getUserPhone(), notConnectionForSMS);
        }

        testCount += 1;

        LGPRSClient clientTest;

        if (clientTest.connect("asasas", port)) {

          if (debug) {

            Serial.println("testRequestToServer: ok");
          }

          setConnectionIsActive(true);

          clientTest.stop();

          return false;
        } else {

          if (debug) {

            Serial.println("testRequestToServer: ko!");
          }

          setConnectionIsActive(false);

          clientTest.stop();

          return true;
        }
      }
    }
  } else {

    testCount = 0;

    setConnectionIsActive(true);

    return true;
  }
}
