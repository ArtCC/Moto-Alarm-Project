// Import classes and libraries
#include "ImportClasses.h"

// Variables
#ifdef APP_LOG
#undef APP_LOG
#endif
#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
  Serial.println();

GATTS uart;

// Functions
void activateBluetoothModule() {

  if (isDebug()) {

    APP_LOG("BLE starts");
  }

  const char *deviceName = deviceNameForBluetooth;
  bool success = LBTServer.begin((uint8_t*) deviceName);

  if (success) {

    if (isDebug()) {

      APP_LOG("BT config sucessfully");
    }

    // Disconnecting BT for opening BLE
    LBTServer.end();

    // LinkIt will work as peripheral, so it assumes the role of GATT Server
    // The GATT server for this example is initialized with only one profile
    if (!LGATTServer.begin(1, &uart)) {

      if (isDebug()) {

        APP_LOG("[FAILED] GATTS begin");
      }
    } else {

      if (isDebug()) {

        APP_LOG("GATTS begin");
      }
    }
  } else {

    LBTServer.end();

    if (isDebug()) {

      Serial.println("[FAILED] BT config successfully");
    }
  }
}

void subscribeToEventsBluetoothModule() {
  // Initialization of the GATT handle
  LGATTServer.handleEvents();
}

bool uartIsActive() {

  if (uart.isConnected()) {

    return true;
  } else {

    return false;
  }
}

bool serviceIsActiveForSendDataToService() {

  if (uart.isServiceActive()) {

    return true;
  } else {

    return false;
  }
}

void setServiceStatus(const bool &newStatus) {
  uart._serviceActivated = newStatus;
}

void sendInfoWithBluetoothModule(char* text) {

  if (uart.isConnected()) {

    if (isDebug()) {

      Serial.println("Send message to principal device...");
    }

    bool msgSuccess = uart.sendMessage(text);

    if (!msgSuccess) {

      if (isDebug()) {

        APP_LOG("[FAILED] send [%d]", msgSuccess);
      }
    } else {

      if (isDebug()) {

        APP_LOG("send [%d][%s]", msgSuccess, text);
      }
    }
  }
}
