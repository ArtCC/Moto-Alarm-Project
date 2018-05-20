// Import classes and libraries
#include "ImportClasses.h"
#include "GATTService.h"

// Properties
GATTService serv;

String temporalUserToken = "Bearer ";

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
  String userIdPrefix = "usrId:";
  String userPhonePrefix = "phone:";
  String tokenPrefix = "token:";

  if (checkIfStringContainOtherString(message, userIdPrefix)) {

    String finalMessage = message;
    finalMessage.replace(userIdPrefix, "");

    setUserId(finalMessage);
  } else if (checkIfStringContainOtherString(message, userPhonePrefix)) {

    String finalMessage = message;
    finalMessage.replace(userPhonePrefix, "");

    setUserPhone(finalMessage);
  } else if (checkIfStringContainOtherString(message, tokenPrefix)) {

    String finalMessage = message;
    finalMessage.replace(tokenPrefix, "");

    temporalUserToken.concat(finalMessage);

    setUserToken(temporalUserToken);

    if (debug) {

      Serial.println("User token");
      Serial.println(temporalUserToken);
    }
  } else if (checkIfStringContainOtherString(message, serviceOn)) {

    setServiceStatus(true);

    if (debug) {

      Serial.println("Status for service: ");
      Serial.println((getServiceStatus()) ? "On" : "Off");
    }
  } else if (checkIfStringContainOtherString(message, serviceOff)) {

    setServiceStatus(false);

    if (debug) {

      Serial.println("Status for service: ");
      Serial.println((getServiceStatus()) ? "On" : "Off");
    }

    // Not update user data but send disable service
    setStatusToUpdateDataToOffUtil(false);
  }
}

void subscribeToEventsBluetoothModule() {
  LGATTServer.handleEvents();
}
