// Import classes and libraries
#include "ImportClasses.h"

// Properties
// "Multi-thread" with millis()
unsigned long intervalToken = 172800000;
unsigned long alarmIntervalUpdate = 60000;
unsigned long disabledIntervalUpdate = 86400000;
unsigned long intervalUpdateForError = 120000;
unsigned long previousMillisToken = 0;
unsigned long previousMillisUpdate = 0;
unsigned long previousMillisUpdateForAlarm = 0;
unsigned long previousMillisForError = 0;

bool firstInit = true;
bool wifiOK = false;
bool gprsOK = false;
bool gpsOK = false;

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

    previousMillisToken = millis();
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
// Config
void configureGPRSConnection() {

  if (isDebug()) {

    Serial.println("APN name: ");
    Serial.println(APN_NAME);
  }

  while (!LGPRS.attachGPRS(APN_NAME, APN_USER, APN_PASSWORD)) {

    if (isDebug()) {

      Serial.println("LGPRS setup error");
    }

    delay(200);

    gprsOK = false;
  }

  if (isDebug()) {

    Serial.println("LGPRS setup correct");
  }

  gprsOK = true;
}

void configureWiFi() {
  LWiFi.begin();

  Serial.println("Connecting to WiFi...");

  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) {

    Serial.println("Error connecting to WiFi...");

    delay(200);

    wifiOK = false;
  }

  Serial.println("Connect to WiFi OK!");

  wifiOK = true;
}

void configureServices() {
  Serial.begin(115200);

  activateBluetoothModule();
  activateSIM();
  activateGPS();

  if (wifiIsActive) {

    configureWiFi();
  } else {

    configureGPRSConnection();
  }

  configureOTAUpdate();
}

void sendUserDataToServerForAlarmIsActive() {
  unsigned long currentMillisUpdate = millis();

  if ((unsigned long)(currentMillisUpdate - previousMillisUpdateForAlarm) >= alarmIntervalUpdate) {

    setStatusToUpdateDataToOnUtil();

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
  setStatusToUpdateDataToOff(getBatteryLevel(),
                             getBatteryChargeStatus(),
                             gpsError);
}

void startSubscribeServices() {
  subscribeToEventsBluetoothModule();
  receivedSMS();
}

void startAllServices() {

  if (firstInit) {

    configureForFirstInit();
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

          setStatusToUpdateDataToOnUtil();

          previousMillisUpdate = millis();
        }
      } else {

        if ((unsigned long)(currentMillisUpdate - previousMillisForError) >= intervalUpdateForError) {

          if (isDebug()) {

            Serial.println("GPS error! Reload!");
          }

          setStatusToUpdateDataToOnUtil();

          previousMillisForError = millis();
        }
      }
    } else if (!serviceIsActiveForSendDataToService()) {

      if ((unsigned long)(currentMillisUpdate - previousMillisUpdate) >= disabledIntervalUpdate) {

        // Not update user data
        setStatusToUpdateDataToOffUtil(false);

        previousMillisUpdate = millis();
      }
    }
  }

  updateDevice();
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

bool getConfigWiFiIsOK() {

  return wifiOK;
}

bool getConfigGPRSIsOK() {

  return gprsOK;
}
