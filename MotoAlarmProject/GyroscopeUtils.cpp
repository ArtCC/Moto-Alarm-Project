// Import classes and libraries
#include "ImportClasses.h"

// Properties
// Control for LSM6DS30 and get first value
bool setNewValuesFromGroveSensor = true;
bool sendDataToServerForAlarmIsActive;

// Accelerometer and gyroscope
int firstGyroscopeX;
int firstGyroscopeY;
int differenceGyroscopeX;
int differenceGyroscopeY;

// Public functions
bool getIfAlarmIsActive() {

  return sendDataToServerForAlarmIsActive;
}

void setAlarmIsActive(const bool &newValue) {
  sendDataToServerForAlarmIsActive = newValue;
}

void setSaveValuesFromGroveSensor(const bool &newValue) {
  setNewValuesFromGroveSensor = newValue;
  sendDataToServerForAlarmIsActive = false;
}

void processValuesFromGroveSensor(float aX,
                                  float aY,
                                  float aZ,
                                  float gX,
                                  float gY,
                                  float gZ,
                                  float temperature) {

  if (setNewValuesFromGroveSensor) {

    if (debug) {

      Serial.println("Get first parameters for LSM6DS3");
    }

    firstGyroscopeX = gX;
    firstGyroscopeY = gY;
    setNewValuesFromGroveSensor = false;
  }

  if (firstGyroscopeX == gX) {

    differenceGyroscopeX = 0;
  } else if (firstGyroscopeX > gX) {

    differenceGyroscopeX = firstGyroscopeX - gX;
  } else if (gX > firstGyroscopeX) {

    differenceGyroscopeX = gX - firstGyroscopeX;
  }

  if (firstGyroscopeY == gY) {

    differenceGyroscopeY = 0;
  } else if (firstGyroscopeY > gY) {

    differenceGyroscopeY = firstGyroscopeY - gY;
  } else if (gY > firstGyroscopeY) {

    differenceGyroscopeY = gY - firstGyroscopeY;
  }

  if (differenceGyroscopeX > 50 && differenceGyroscopeY > 50) {

    deleteFileFromSDCard(motorbikePositionHistorial);

    sendDataToServerForAlarmIsActive = true;

    sendSMSToPhoneNumber(getUserPhone(), textForAlarmSMSWithoutLocation);

    if (debug) {

      Serial.println("Alert!");
      Serial.println();
    }
  }

  if (debug) {

    // Accelerometer
    Serial.print("\nAccelerometer:\n");
    Serial.print(" X1 = ");
    Serial.println(aX);
    Serial.print(" Y1 = ");
    Serial.println(aY);
    Serial.print(" Z1 = ");
    Serial.println(aZ);

    // Gyroscope
    Serial.print("\nGyroscope:\n");
    Serial.print(" X1 = ");
    Serial.println(gX);
    Serial.print(" Y1 = ");
    Serial.println(gY);
    Serial.print(" Z1 = ");
    Serial.println(gZ);

    // Thermometer
    Serial.print("\nThermometer: ");
    Serial.print(temperature);
    Serial.println("*C");
    Serial.println();

    // Differences between values
    Serial.print("Difference between gyroscope X: ");
    Serial.println(differenceGyroscopeX);
    Serial.print("Difference between gyroscope Y: ");
    Serial.println(differenceGyroscopeY);
    Serial.println();
  }
}
