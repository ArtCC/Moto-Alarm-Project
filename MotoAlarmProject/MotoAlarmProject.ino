/**
   Moto Alarm Project

   This project is free and use CC BY-NC-SA:
   This license lets others remix, tweak, and build upon your work, as long as they credit you and license their new creations under the identical terms.
   This license is often compared to “copyleft” free and open source software licenses. All new works based on yours will carry the same license.

   ArtCC 2017++

   Enjoy it! :)
*/

// Import classes and libraries
#include "ImportClasses.h"

// Properties
// Instance for MPU6050 module
MPU6050 mpu;

// Public functions
void setup() {
  configureServices();
  configureMPU6050Module();
}

void loop() {
  startSubscribeServices();

  if (getServiceStatus()) {

    if (getIfAlarmIsActive()) {

      startAllServices();
    } else {

      startMPU6050Module();
    }
  } else {

    stopServices();
  }
}

// Private functions
// MPU6050 config
void configureMPU6050Module() {

  if (debug) {

    Serial.println("Initialize MPU6050");
  }

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {

    if (debug) {

      Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    }

    delay(100);
  }
}

void startMPU6050Module() {
  unsigned long currentMillisUpdateForMPU6050 = millis();

  if ((unsigned long)(currentMillisUpdateForMPU6050 - previousMillisForMPU6050) >= intervalUpdateForMPU6050) {

    // Read normalized values
    Vector normAccel = mpu.readNormalizeAccel();

    // Calculate pitch, roll, temperature meditions and send to process
    int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
    int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;
    float temp = mpu.readTemperature();

    processValuesFromMPU6050(pitch,
                             roll,
                             temp);

    previousMillisForMPU6050 = millis();
  }
}
