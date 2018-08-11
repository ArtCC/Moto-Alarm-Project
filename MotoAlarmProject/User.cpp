// Import classes and libraries
#include "ImportClasses.h"

void User::setUserToken(String &string) {
  userToken = string;

  card.deleteFileFromSDCard(tokenFile);
  card.setDataInFile(tokenFile, userToken);
}

void User::setUserId(String &string) {
  userId = string;

  card.deleteFileFromSDCard(userIdFile);
  card.setDataInFile(userIdFile, userId);
}

void User::setUserPhone(String &string) {
  userPhone = string;

  card.deleteFileFromSDCard(userPhoneFile);
  card.setDataInFile(userPhoneFile, userPhone);
}

void User::setAPNName(String &string) {
  apnName = string;

  card.deleteFileFromSDCard(apnNameFile);
  card.setDataInFile(apnNameFile, apnName);
}

void User::setAPNUser(String &string) {
  apnUser = string;

  card.deleteFileFromSDCard(apnUserFile);
  card.setDataInFile(apnUserFile, apnUser);
}

void User::setAPNPassword(String &string) {
  apnPassword = string;

  card.deleteFileFromSDCard(apnPasswordFile);
  card.setDataInFile(apnPasswordFile, apnPassword);
}

void User::setDeviceNameForBluetooth(String &string) {
  deviceName = string;

  card.deleteFileFromSDCard(deviceNameFile);
  card.setDataInFile(deviceNameFile, deviceName);
}

String User::getUserToken() {

  if (card.checkIFFileExistInSDCard(tokenFile)) {

    userToken = card.getDataFromFile(tokenFile);
  }

  String modifyToken = userToken;
  modifyToken.trim();

  return modifyToken;
}

String User::getUserId() {

  if (card.checkIFFileExistInSDCard(userIdFile)) {

    userId = card.getDataFromFile(userIdFile);
  }

  String modifyUserId = userId;
  modifyUserId.trim();

  return modifyUserId;
}

String User::getUserPhone() {

  if (card.checkIFFileExistInSDCard(userPhoneFile)) {

    userPhone = card.getDataFromFile(userPhoneFile);
  }

  String modifyUserPhone = userPhone;
  modifyUserPhone.trim();

  return modifyUserPhone;
}

String User::getAPNName() {
  String modifyApnName = "";

  if (card.checkIFFileExistInSDCard(apnNameFile)) {

    apnName = card.getDataFromFile(apnNameFile);
    modifyApnName = apnName;
  }

  modifyApnName.trim();

  return modifyApnName;
}

String User::getAPNUser() {
  String modifyApnUser = "";

  if (card.checkIFFileExistInSDCard(apnUserFile)) {

    apnUser = card.getDataFromFile(apnUserFile);
    modifyApnUser = apnUser;
  }

  modifyApnUser.trim();

  return modifyApnUser;
}

String User::getAPNPassword() {
  String modifyApnPassword = "";

  if (card.checkIFFileExistInSDCard(apnPasswordFile)) {

    apnPassword = card.getDataFromFile(apnPasswordFile);
    modifyApnPassword = apnPassword;
  }

  modifyApnPassword.trim();

  return modifyApnPassword;
}

String User::getDeviceNameForBluetooth() {
  String modifyDeviceName = "MotoAlarmProject";

  if (card.checkIFFileExistInSDCard(deviceNameFile)) {

    deviceName = card.getDataFromFile(deviceNameFile);
    modifyDeviceName = deviceName;
  }

  modifyDeviceName.trim();

  return modifyDeviceName;
}

bool User::getServiceStatusFromPersist() {

  if (card.checkIFFileExistInSDCard(serviceStatusFile)) {

    String serviceStatus = card.getDataFromFile(serviceStatusFile);
    serviceStatus.trim();

    if (serviceStatus == kServiceStatusActivated) {

      return true;
    } else if (serviceStatus == kServiceStatusActivated) {

      return false;
    }
  }

  return false;
}
