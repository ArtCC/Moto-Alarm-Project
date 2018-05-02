// Import classes and libraries
#include "ImportClasses.h"

// Variables
// "Multi-thread" with millis()
unsigned long intervalToken = 259200000;
unsigned long alarmIntervalUpdate = 30000;
unsigned long disabledIntervalUpdate = 3600000;
unsigned long previousMillisToken = 0;
unsigned long previousMillisUpdate = 0;

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

      bool response = getTokenForUser();

      if (response) {

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
  bool response = getTokenForUser();

  if (response) {

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

  bool resultForGetDeviceUpdateTime = getDeviceUpdateTime();

  if (resultForGetDeviceUpdateTime) {

    if (isDebug()) {

      Serial.println("Get new device update time correct");
    }
  }

  setStatusToUpdateDataToOnUtil();
}

// Public functions
void configureServices() {
  Serial.begin(115200);

  configureGPRSConnection();
  activateBluetoothModule();
  activateSIM();
  activateGPS();
}

void setStatusToUpdateDataToOnUtil() {
  bool gpsResult = activateGPSData();

  if (gpsResult) {

    // Update user data
    setUpdateDataUserToServer(
      getLatitude(),
      getLongitude(),
      getBatteryLevel(),
      getBatteryChargeStatus()
    );
  } else {

    // Not update user data
    setStatusToUpdateDataToOffUtil();
  }
}

void setStatusToUpdateDataToOffUtil() {
  alarmSMSActive = true;

  setStatusToUpdateDataToOff(getBatteryLevel(),
                             getBatteryChargeStatus());
}

void startAllServices() {
  subscribeToEventsBluetoothModule();
  receivedSMS();

  if (firstInit) {

    if (getStatusCorrectConnection()) {

      configureForFirstInit();
    }
  } else {

    updateToken();

    unsigned long currentMillisUpdate = millis();

    if (serviceIsActiveForSendDataToService() == true) {

      long finalIntervalUpdate = getValueForDeviceUpdateTime();

      if (getVelocity() >= 3.0) {

        finalIntervalUpdate = alarmIntervalUpdate;

        if (alarmSMSActive == true) {

          String textString = textForAlarmSMS + String(getVelocity()) + "m/s";

          if (isDebug()) {

            Serial.println("SMS: Alert");
            Serial.println(textString);
          }

          sendSMSToPhoneNumber(userPhone, textString);
          alarmSMSActive = false;
        }
      }

      if (isDebug()) {

        Serial.println("Time for data user new update:");
        Serial.println(currentMillisUpdate);
        Serial.println(previousMillisUpdate);
        Serial.println(finalIntervalUpdate);
      }

      if ((unsigned long)(currentMillisUpdate - previousMillisUpdate) >= finalIntervalUpdate) {

        if (getStatusCorrectConnection()) {

          setStatusToUpdateDataToOnUtil();
        }

        previousMillisUpdate = millis();
      }
    } else if (serviceIsActiveForSendDataToService() == false) {

      if ((unsigned long)(currentMillisUpdate - previousMillisUpdate) >= disabledIntervalUpdate) {

        if (getStatusCorrectConnection()) {

          // Not update user data
          setStatusToUpdateDataToOffUtil();
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
  String text = getCity() + ": " + getWeatherTitle() + ", " + getTemp() + "C, " + getHumidity() + "%H";

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
