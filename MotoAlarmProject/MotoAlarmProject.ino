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
// Create a instance of class LSM6DS3, I2C device address 0x6A
LSM6DS3 groveSensor(I2C_MODE, 0x6A);

// Public functions
void setup() {
  configureServices();
  configureGroveSensorModule();
}

void loop() {
  startSubscribeServices();

  if (getServiceStatus()) {

    if (getIfAlarmIsActive()) {

      startAllServices();
    } else {

      startGroveSensorModule();
    }
  } else {

    stopServices();
  }

  checkStatusService();
}

// Private functions
// LSM6DS3 config
void configureGroveSensorModule() {

  if (debug) {

    Serial.println("Initialize LSM6DS3");
  }

  while (groveSensor.begin() != 0) {

    if (debug) {

      Serial.println("Could not find a valid LSM6DS3 sensor, check wiring!");
    }

    delay(100);
  }
}

void startGroveSensorModule() {
  unsigned long currentMillisUpdateForGroveSensor = millis();

  if ((unsigned long)(currentMillisUpdateForGroveSensor - previousMillisForGroveSensor) >= intervalUpdateForGroveSensor) {

    processValuesFromGroveSensor(groveSensor.readFloatAccelX(),
                                 groveSensor.readFloatAccelY(),
                                 groveSensor.readFloatAccelZ(),
                                 groveSensor.readFloatGyroX(),
                                 groveSensor.readFloatGyroY(),
                                 groveSensor.readFloatGyroZ(),
                                 groveSensor.readTempC());

    previousMillisForGroveSensor = millis();
  }
}
