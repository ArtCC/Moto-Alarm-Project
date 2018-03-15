// Import classes and libraries
#include "ImportClasses.h"

// Variables
// "Multi-thread" with millis()
unsigned long intervalToken = 259200000;
unsigned long intervalUpdate = 120000;
unsigned long alarmIntervalUpdate = 30000;
unsigned long disabledIntervalUpdate = 900000;
unsigned long previousMillisToken = 0;
unsigned long previousMillisUpdate = 0;

// SMS
String textForWetSMS = "I'm very wet... ";
String textForColdSMS = "I'm very cold... ";
String textForHotSMS = "I'm very hot... ";
String textForAlarmSMS = "Your motorcycle is moving: ";

// Private functions
void configureGPRSConnection() {
  while (!LGPRS.attachGPRS(apnName, apnUser, apnPassword)) {

    Serial.println("LGPRS setup error");
    delay(100);
  }

  Serial.println("LGPRS setup correct");
}

void setStatusToUpdateDataToOffUtil() {
  alarmSMSActive = false;

  setStatusToUpdateDataToOff(getBatteryLevel(),
                             getBatteryChargeStatus());
}

// Public functions
void configureServices() {
  Serial.begin(115200);

  configureGPRSConnection();
  activateBluetoothModule();
  activateSIM();
  activateGPS();
  beginModuleForUpdate();
}

void startAllServices() {
  subscribeToEventsBluetoothModule();
  receivedSMS();
  checkIfExistUpdateInServer();

  if (firstInit) {

    bool response = getTokenForUser();

    if (response) {

      firstInit = false;
    } else {

      firstInit = true;
    }
  } else {

    unsigned long currentMillisToken = millis();
    unsigned long currentMillisUpdate = millis();

    if ((unsigned long)(currentMillisToken - previousMillisToken) >= intervalToken) {

      bool response = getTokenForUser();

      if (response) {

        if (isDebug()) {

          Serial.println("Token ok");
        }
      } else {

        firstInit = true;
      }

      previousMillisToken = millis();
    }

    long finalIntervalUpdate = intervalUpdate;

    if (getVelocity() > 9.0) {

      finalIntervalUpdate = alarmIntervalUpdate;
      setServiceStatus(true);

      if (alarmSMSActive == true) {

        String textString = textForAlarmSMS + getVelocity() + "m/s";
        sendSMSToPhoneNumber(userPhone, textString);
        alarmSMSActive = false;
      }
    }

    if (serviceIsActiveForSendDataToService() == true) {

      if ((unsigned long)(currentMillisUpdate - previousMillisUpdate) >= finalIntervalUpdate) {

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

        previousMillisUpdate = millis();
      }
    } else if (serviceIsActiveForSendDataToService() == false) {

      if ((unsigned long)(currentMillisUpdate - previousMillisUpdate) >= disabledIntervalUpdate) {

        // Not update user data
        setStatusToUpdateDataToOffUtil();

        previousMillisUpdate = millis();
      }
    }
  }
}

bool isDebug() {

  return debug;
}

String getFeel() {
  String text = getCity() + ": " + getWeatherTitle() + " - " + getTemp() + "C - " + getHumidity() + "%";

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

  if (isDebug()) {

    Serial.println("Now we are Resetting Arduino Programmatically");
  }
}
