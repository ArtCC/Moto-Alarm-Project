// Import classes and libraries
#include "ImportClasses.h"
#include "GATTService.h"

// Properties
GATTService serv;

// Functions
void activateBluetoothModule() {

  if (LBTServer.begin((uint8_t *)bluetoothDeviceName)) {

    if (debug) {

      Serial.println("BT config sucessfully");
    }
  }

  if (LGATTServer.begin(1, &serv)) {

    if (debug) {

      Serial.println("GATT Server Started");
    }
  } else {

    if (debug) {

      Serial.println("Error Starting GATT Server");
    }
  }
}

void receivedNewMessageFromBluetooth(String &message) {

  if (message == serviceOff) {

    serviceActive = false;
    userToken = "";
  } else {

    serviceActive = true;
    userToken.concat(message);
  }

  if (debug) {

    Serial.println("Status for service: ");
    Serial.println((serviceActive) ? "On" : "Off");
    Serial.println("User token");
    Serial.println(userToken);
  }
}

void subscribeToEventsBluetoothModule() {
  LGATTServer.handleEvents();
}
