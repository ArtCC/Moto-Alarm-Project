// Import classes and libraries
#include "ImportClasses.h"

// Public functions
String getBatteryLevel() {

  return String(LBattery.level());
}

String getBatteryChargeStatus() {

  return String(LBattery.isCharging());
}

bool stringIsEmpty(String &string) {
  int lengthString = string.length();

  if (lengthString > 0) {

    return true;
  }

  return false;
}

bool checkIfStringContainOtherString(String &string, String &search) {

  if (string.substring(0, 6) == search) {

    return true;
  }

  return false;
}
