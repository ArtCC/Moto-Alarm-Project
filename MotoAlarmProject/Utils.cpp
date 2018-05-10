// Import classes and libraries
#include "ImportClasses.h"

// Variables
// "Multi-thread" with millis()
unsigned long intervalToken = 172800000;
unsigned long alarmIntervalUpdate = 60000;
unsigned long disabledIntervalUpdate = 86400000;
unsigned long intervalUpdateForError = 120000;
unsigned long previousMillisToken = 0;
unsigned long previousMillisUpdate = 0;
unsigned long previousMillisUpdateForAlarm = 0;
unsigned long previousMillisForError = 0;

// Private functions
// Reset Controller
extern void vm_reboot_normal_start(void);

void vm_reset_utils(void) {

  if (isDebug()) {

    Serial.println("Reset...");
  }

  delay(500);
  vm_reboot_normal_start();
}

boolean vm_reset_wrap_utils(void* userData) {
  vm_reset_utils();

  return true;
}

void reset_utils(void) {
  LTask.remoteCall(vm_reset_wrap_utils, NULL);
}

// Update token
void updateToken() {
  unsigned long currentMillisToken = millis();

  if ((unsigned long)(currentMillisToken - previousMillisToken) >= intervalToken) {

    if (getStatusCorrectConnection()) {

      if (getTokenForUser()) {

        if (isDebug()) {

          Serial.println("Refresh token ok");
        }
      } else {

        if (isDebug()) {

          Serial.println("Refresh token ko");
        }

        firstInit = true;
      }
    }

    previousMillisToken = millis();
  }
}

// Config
void configureGPRSConnection() {
  while (!LGPRS.attachGPRS(apnName, apnUser, apnPassword)) {

    if (isDebug()) {

      Serial.println("LGPRS setup error");
    }

    delay(100);
  }

  if (isDebug()) {

    Serial.println("LGPRS setup correct");
  }
}

void configureForFirstInit() {

  if (getTokenForUser()) {

    if (isDebug()) {

      Serial.println("New token ok");
    }

    firstInit = false;
  } else {

    if (isDebug()) {

      Serial.println("New token ko");
    }

    firstInit = true;
  }

  if (getDeviceUpdateTime()) {

    if (isDebug()) {

      Serial.println("Get new device update time correct");
    }
  }

  setStatusToUpdateDataToOffUtil(false);
}

// Public functions
void configureServices() {
  Serial.begin(115200);

  configureGPRSConnection();
  activateBluetoothModule();
  activateSIM();
  activateGPS();
}

void sendUserDataToServerForAlarmIsActive() {
  unsigned long currentMillisUpdate = millis();

  if ((unsigned long)(currentMillisUpdate - previousMillisUpdateForAlarm) >= alarmIntervalUpdate) {

    if (getStatusCorrectConnection()) {

      setStatusToUpdateDataToOnUtil();
    }

    previousMillisUpdateForAlarm = millis();
  }
}

void setStatusToUpdateDataToOnUtil() {

  if (activateGPSData()) {

    gpsOK = true;

    // Update user data
    setUpdateDataUserToServer(
      getLatitude(),
      getLongitude(),
      getBatteryLevel(),
      getBatteryChargeStatus()
    );
  } else {

    gpsOK = false;

    // Not update user data
    setStatusToUpdateDataToOffUtil(true);
  }
}

void setStatusToUpdateDataToOffUtil(const bool &gpsError) {
  alarmSMSActive = true;

  setStatusToUpdateDataToOff(getBatteryLevel(),
                             getBatteryChargeStatus(),
                             gpsError);
}

void startSubscribeServices() {
  subscribeToEventsBluetoothModule();
  receivedSMS();

  if (firstInit) {

    if (getStatusCorrectConnection()) {

      configureForFirstInit();
    }
  } else {

    updateToken();

    unsigned long currentMillisUpdate = millis();

    if (serviceIsActiveForSendDataToService()) {

      if (gpsOK) {

        if ((unsigned long)(currentMillisUpdate - previousMillisUpdate) >= getValueForDeviceUpdateTime()) {

          if (isDebug()) {

            Serial.println("Time for data user new update:");
            Serial.println(currentMillisUpdate);
            Serial.println(previousMillisUpdate);
            Serial.println(getValueForDeviceUpdateTime());
            Serial.println("");
          }

          if (getStatusCorrectConnection()) {

            setStatusToUpdateDataToOnUtil();
          }

          previousMillisUpdate = millis();
        }
      } else {

        if ((unsigned long)(currentMillisUpdate - previousMillisForError) >= intervalUpdateForError) {

          if (isDebug()) {

            Serial.println("GPS error! Reload!");
          }

          if (getStatusCorrectConnection()) {

            setStatusToUpdateDataToOnUtil();
          }

          previousMillisForError = millis();
        }
      }
    } else if (!serviceIsActiveForSendDataToService()) {

      if ((unsigned long)(currentMillisUpdate - previousMillisUpdate) >= disabledIntervalUpdate) {

        if (getStatusCorrectConnection()) {

          // Not update user data
          setStatusToUpdateDataToOffUtil(false);
        }

        previousMillisUpdate = millis();
      }
    }
  }
}

bool isDebug() {

  return debug;
}

String getFeel() {
  String text = getCity() + ": " + getWeatherTitle() + ", " + getTemp() + "*C, " + getHumidity() + "%H";

  int temp = getTemp().toInt();
  int humidity = getHumidity().toInt();

  String statusString = "";

  if (temp < 10) {

    if (humidity > 60) {

      statusString = textForWetSMS;
    } else {

      statusString = textForColdSMS;
    }
  } else {

    if (humidity > 60) {

      statusString = textForWetSMS;
    } else {

      statusString = textForHotSMS;
    }
  }

  return statusString + text;
}

void resetByCode() {
  delay(5000);

  if (isDebug()) {

    Serial.println("Now we are Resetting Arduino Programmatically");
  }

  reset_utils();
}
