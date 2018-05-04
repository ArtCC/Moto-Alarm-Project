/**
   Moto Alarm Project

   This project is free and use CC BY-SA:
   This license lets others remix, tweak, and build upon your work even for commercial purposes, as long as they credit you and license their new creations under the identical terms.
   This license is often compared to “copyleft” free and open source software licenses. All new works based on yours will carry the same license, so any derivatives will also allow commercial use.
   This is the license used by Wikipedia, and is recommended for materials that would benefit from incorporating content from Wikipedia and similarly licensed projects.

   ArtCC 2017++

   Enjoy it! :)
*/

// Import classes and libraries
#include "ImportClasses.h"

// Properties
// Instance for MPU6050 module
MPU6050 mpu;

// Control for MPU6050 and get first value
bool initMPU6050 = false;

// Accelerometer and gyroscope
int firstRoll;

// Functions
void setup() {
  configureMPU6050Module();
  configureServices();
}

void loop() {
  startMPU6050Module();
  startAllServices();
}

// Private functions
// MPU6050 config
void configureMPU6050Module() {

  if (isDebug()) {

    Serial.println("Initialize MPU6050");
  }

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {

    if (isDebug()) {

      Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    }

    delay(100);
  }
}

void startMPU6050Module() {
  // Read normalized values
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate roll meditions
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;

  // Temperature
  float temp = mpu.readTemperature();

  if (!initMPU6050) {

    if (isDebug()) {

      Serial.println("Get first parameters for MPU6050");
    }

    firstRoll = roll;
    initMPU6050 = true;
  }

  if (isDebug()) {

    Serial.print("First roll: ");
    Serial.print(firstRoll);
    Serial.println("");

    Serial.println("");
    Serial.print("Actual roll: ");
    Serial.print(roll);
    Serial.println("");

    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" *C");
    Serial.println("");
  }

  if (firstRoll == roll) {

    Serial.println("Not alert");
  } else {

    Serial.println("Alert");
  }

  Serial.println("");

  delay(100);
}

void stopMPU6050Module() {
}
