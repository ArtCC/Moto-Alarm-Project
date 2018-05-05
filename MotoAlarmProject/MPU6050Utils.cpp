// Import classes and libraries
#include "ImportClasses.h"

// Properties
// Control for MPU6050 and get first value
bool initMPU6050 = false;

// Accelerometer and gyroscope
int firstPitch;
int firstRoll;
int differencePitch;
int differenceRoll;

// Public functions
void processValuesFromMPU6050(int &pitch, int &roll, float &temperature) {

  if (!initMPU6050) {

    if (isDebug()) {

      Serial.println("Get first parameters for MPU6050");
    }

    firstPitch = pitch;
    firstRoll = roll;
    initMPU6050 = true;
  }

  if (firstPitch == pitch) {

    differencePitch = 0;
  } else if (firstPitch > pitch) {

    differencePitch = firstPitch - pitch;
  } else if (pitch > firstPitch) {

    differencePitch = pitch - firstPitch;
  }

  if (firstRoll == roll) {

    differenceRoll = 0;
  } else if (firstRoll > roll) {

    differenceRoll = firstRoll - roll;
  } else if (roll > firstRoll) {

    differenceRoll = roll - firstRoll;
  }

  if (differencePitch > 10 || differenceRoll > 10) {

    if (isDebug()) {

      Serial.println("Alert!");
      Serial.println();
    }
  }

  if (isDebug()) {

    Serial.print("First pitch: ");
    Serial.println(firstPitch);
    Serial.print("Actual pitch: ");
    Serial.println(pitch);
    Serial.print("First roll: ");
    Serial.println(firstRoll);
    Serial.print("Actual roll: ");
    Serial.println(roll);
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.println("*C");
    Serial.print("Difference between pitch: ");
    Serial.println(differencePitch);
    Serial.print("Difference between roll: ");
    Serial.println(differenceRoll);
    Serial.println();
  }
}
