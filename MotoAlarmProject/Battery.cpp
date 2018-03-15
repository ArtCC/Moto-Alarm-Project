// Import classes and libraries
#include "ImportClasses.h"

// Public functions
String getBatteryLevel() {

  return String(LBattery.level());
}

String getBatteryChargeStatus() {

  return String(LBattery.isCharging());
}
