// Import classes and libraries
#include "ImportClasses.h"

// Properties
// "Multi-thread" with millis()
unsigned long previousMillisForSendData = 0;
unsigned long disabledIntervalUpdate = 86400000;
unsigned long disabledPreviousMillisUpdate = 0;

// Others
bool firstInit = true;
bool checkStatusServiceValue = false;

// Private functions
// Reset Controller
extern void vm_reboot_normal_start(void);

void vm_reset_utils(void) {

  if (debug) {

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

void configureGPRSConnection() {
  String apnNameString = user.getAPNName();
  String apnUserString = user.getAPNUser();
  String apnPasswordString = user.getAPNPassword();

  char toCharAPNName[100];
  apnNameString.toCharArray(toCharAPNName, 100);
  char *apnName = toCharAPNName;

  char toCharAPNUser[100];
  apnUserString.toCharArray(toCharAPNUser, 100);
  char *apnUser = toCharAPNUser;

  char toCharAPNPassword[100];
  apnPasswordString.toCharArray(toCharAPNPassword, 100);
  char *apnPassword = toCharAPNPassword;

  while (!LGPRS.attachGPRS(apnName, apnUser, apnPassword)) {

    if (debug) {

      Serial.println("LGPRS setup error");
    }

    delay(200);
  }

  if (debug) {

    Serial.println("LGPRS setup correct");
  }
}

void configureForFirstInit() {

  if (firstInit) {

    if (getDeviceUpdateTime()) {

      if (debug) {

        Serial.println("Get new device update time correct");
      }

      firstInit = false;
    } else {

      if (debug) {

        Serial.println("Get new device update time incorrect");
      }

      firstInit = true;
    }
  }
}

void setStatusToUpdateDataToOnUtil() {

  if (activateGPSData()) {

    // Update user data
    setUpdateDataUserToServer(
      getLatitude(),
      getLongitude(),
      getBatteryLevel(),
      getBatteryChargeStatus()
    );
  } else {

    setStatusToUpdateDataToOffUtil(true);
  }
}

void setStatusToUpdateDataToOffUtil(const bool &gpsError) {
  setStatusToUpdateDataToOff(getBatteryLevel(),
                             getBatteryChargeStatus(),
                             gpsError);
}

// Public functions
void configureServices() {
  Serial.begin(115200);

  card.configSDCard();
  bluetooth.activateBluetoothModule();
  activateGPS();
  activateSIM();
  configureGPRSConnection();
  configureOTAUpdate();
}

void startSubscribeServices() {
  receivedSMS();
  bluetooth.subscribeToEventsBluetoothModule();
  updateDevice();
}

void checkStatusService() {

  if (!checkStatusServiceValue) {

    if (debug) {

      Serial.println("Check status service from reset...");
    }

    if (user.getServiceStatusFromPersist()) {

      setServiceStatus(true);
    } else {

      setServiceStatus(false);
      gyroscope.setAlarmIsActive(false);
    }

    checkStatusServiceValue = true;
  }
}

void startAllServices() {
  configureForFirstInit();

  unsigned long currentMillisUpdateForSendData = millis();

  if (!firstInit) {

    if ((unsigned long)(currentMillisUpdateForSendData - previousMillisForSendData) >= getValueForDeviceUpdateTime()) {

      if (debug) {

        Serial.println("Time for data user new update:");
        Serial.println(currentMillisUpdateForSendData);
        Serial.println(previousMillisForSendData);
        Serial.println(getValueForDeviceUpdateTime());
        Serial.println("");
      }

      String location = getLatitude() + "," + getLongitude();
      card.setDataInFile(motorbikePositionHistorial, location);

      setStatusToUpdateDataToOnUtil();

      previousMillisForSendData = millis();
    }
  }
}

void stopServices() {
  unsigned long disabledCurrentMillisUpdate = millis();

  if ((unsigned long)(disabledCurrentMillisUpdate - disabledPreviousMillisUpdate) >= disabledIntervalUpdate) {

    // Not update user data
    setStatusToUpdateDataToOffUtil(false);

    disabledPreviousMillisUpdate = millis();
  }
}

void setServiceStatus(const bool &value) {
  serviceActive = value;

  card.deleteFileFromSDCard(user.serviceStatusFile);

  if (value) {

    card.setDataInFile(user.serviceStatusFile, user.kServiceStatusActivated);
  } else {

    card.setDataInFile(user.serviceStatusFile, user.kServiceStatusDesactivated);
  }
}

bool getServiceStatus() {

  return serviceActive;
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

  if (debug) {

    Serial.println("Now we are Resetting Arduino Programmatically");
  }

  reset_utils();
}
