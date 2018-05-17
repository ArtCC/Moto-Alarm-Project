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

// Functions
void setup() {
  configureServices();
  configureMPU6050Module();
}

void loop() {

  if (wifiIsActive) {

    if (getConfigWiFiIsOK()) {

      startServices();
    } else {

      checkConnectionStatus(true, false);
    }
  } else {

    if (getConfigGPRSIsOK()) {

      startServices();
    } else {

      checkConnectionStatus(false, true);
    }
  }
}

// Private functions
void checkConnectionStatus(const bool &wifi, const bool &gprs) {
  unsigned long currentMillisUpdate = millis();

  if ((unsigned long)(currentMillisUpdate - previousMillisForConnectionCheck) >= intervalUpdateForConnectionCheck) {

    if (wifi) {

      configureWiFi();
    } else if (gprs) {

      configureGPRSConnection();
    }

    previousMillisForConnectionCheck = millis();
  }
}

void startServices() {
  startSubscribeServices();

  if (getStatusCorrectConnection()) {

    startAllServices();

    if (serviceIsActiveForSendDataToService()) {

      if (!getIfAlarmIsActive()) {

        startMPU6050Module();
      } else {

        sendUserDataToServerForAlarmIsActive();
      }
    }
  } else {

    if (isDebug()) {

      Serial.println("Connection error!");
    }

    delay(3000);
  }
}

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
  unsigned long currentMillisUpdate = millis();

  if ((unsigned long)(currentMillisUpdate - previousMillisForMPU6050) >= intervalUpdateForMPU6050) {

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
