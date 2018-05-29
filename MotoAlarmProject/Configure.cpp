// Import classes and libraries
#include "ImportClasses.h"

// Properties
// "Multi-thread" with millis()
unsigned long previousMillisForSendData = 0;
unsigned long disabledIntervalUpdate = 86400000;
unsigned long disabledPreviousMillisUpdate = 0;

// User
String userPhone = "";
String userId = "";
String userToken = "";

// APN
String apnName = "";
String apnUser = "";
String apnPassword = "";

// Device
String deviceName = "";

// Files card
String tokenFile = "token.txt";
String userIdFile = "userId.txt";
String userPhoneFile = "userPhone.txt";
String apnNameFile = "apnName.txt";
String apnUserFile = "apnUser.txt";
String apnPasswordFile = "apnPass.txt";
String deviceNameFile = "deviceName.txt";

// Others
bool firstInit = true;

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
  String apnNameString = getAPNName();
  String apnUserString = getAPNUser();
  String apnPasswordString = getAPNPassword();

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

  configSDCard();
  activateBluetoothModule();
  activateGPS();
  activateSIM();
  configureGPRSConnection();
  configureOTAUpdate();
}

void startSubscribeServices() {
  receivedSMS();
  subscribeToEventsBluetoothModule();
  updateDevice();
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
      setDataInFile(motorbikePositionHistorial, location);

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

void setUserToken(String &string) {
  userToken = string;

  deleteFileFromSDCard(tokenFile);
  setDataInFile(tokenFile, userToken);
}

void setUserId(String &string) {
  userId = string;

  deleteFileFromSDCard(userIdFile);
  setDataInFile(userIdFile, userId);
}

void setUserPhone(String &string) {
  userPhone = string;

  deleteFileFromSDCard(userPhoneFile);
  setDataInFile(userPhoneFile, userPhone);
}

void setAPNName(String &string) {
  apnName = string;

  deleteFileFromSDCard(apnNameFile);
  setDataInFile(apnNameFile, apnName);
}

void setAPNUser(String &string) {
  apnUser = string;

  deleteFileFromSDCard(apnUserFile);
  setDataInFile(apnUserFile, apnUser);
}

void setAPNPassword(String &string) {
  apnPassword = string;

  deleteFileFromSDCard(apnPasswordFile);
  setDataInFile(apnPasswordFile, apnPassword);
}

void setDeviceNameForBluetooth(String &string) {
  deviceName = string;

  deleteFileFromSDCard(deviceNameFile);
  setDataInFile(deviceNameFile, deviceName);
}

String getUserToken() {

  if (checkIFFileExistInSDCard(tokenFile)) {

    userToken = getDataFromFile(tokenFile);
  }

  String modifyToken = userToken;
  modifyToken.trim();

  return modifyToken;
}

String getUserId() {

  if (checkIFFileExistInSDCard(userIdFile)) {

    userId = getDataFromFile(userIdFile);
  }

  String modifyUserId = userId;
  modifyUserId.trim();

  return modifyUserId;
}

String getUserPhone() {

  if (checkIFFileExistInSDCard(userPhoneFile)) {

    userPhone = getDataFromFile(userPhoneFile);
  }

  String modifyUserPhone = userPhone;
  modifyUserPhone.trim();

  return modifyUserPhone;
}

String getAPNName() {
  String modifyApnName = "";

  if (checkIFFileExistInSDCard(apnNameFile)) {

    apnName = getDataFromFile(apnNameFile);
    modifyApnName = apnName;
  }

  modifyApnName.trim();

  return modifyApnName;
}

String getAPNUser() {
  String modifyApnUser = "";

  if (checkIFFileExistInSDCard(apnUserFile)) {

    apnUser = getDataFromFile(apnUserFile);
    modifyApnUser = apnUser;
  }

  modifyApnUser.trim();

  return modifyApnUser;
}

String getAPNPassword() {
  String modifyApnPassword = "";

  if (checkIFFileExistInSDCard(apnPasswordFile)) {

    apnPassword = getDataFromFile(apnPasswordFile);
    modifyApnPassword = apnPassword;
  }

  modifyApnPassword.trim();

  return modifyApnPassword;
}

String getDeviceNameForBluetooth() {
  String modifyDeviceName = "MotoAlarmProject";

  if (checkIFFileExistInSDCard(deviceNameFile)) {

    deviceName = getDataFromFile(deviceNameFile);
    modifyDeviceName = deviceName;
  }

  modifyDeviceName.trim();

  return modifyDeviceName;
}
