// Import classes and libraries
#include "ImportClasses.h"

// Variables
#ifdef APP_LOG
#undef APP_LOG
#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
  Serial.println();
#endif

// Functions
// Declaration of the service with two characteristics
// As we are not using standard services and characteristics, their UUID's are unique
// Only our software could understand it
static LGATTServiceInfo g_uart_decl[] = {
  {TYPE_SERVICE, "258982b9-ab95-444d-bac8-c04f2dcf8d6e", TRUE, 0, 0, 0},
  {TYPE_CHARACTERISTIC, "39543a26-89a6-4e7b-b96c-83612b7702f2", FALSE, VM_GATT_CHAR_PROP_NOTIFY | VM_GATT_CHAR_PROP_READ, VM_GATT_PERM_READ, 0},
  {TYPE_CHARACTERISTIC, "39543a26-89a6-4e7b-b96c-83612b7702f3", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0},
  {TYPE_END, 0, 0, 0, 0, 0}
};

uint16_t GATTS::getHandle(int32_t type) {

  if (0 == type) {

    return _handle_notify;
  } else if (1 == type) {

    return _handle_write;
  }

  return 0;
}

// Prepare the data for profile
LGATTServiceInfo *GATTS::onLoadService(int32_t index) {

  return g_uart_decl;
}

// Characteristic added
boolean GATTS::onCharacteristicAdded(LGATTAttributeData &data) {
  const VM_BT_UUID *uuid = &(data.uuid);

  if (isDebug()) {

    APP_LOG("LGATTSUart::onCharacteristicAdded f[%d] uuid[12] = [0x%x] len[%d]", data.failed, uuid->uuid[12], uuid->len);
  }

  if (!data.failed) {

    if (0x7E == uuid->uuid[12]) {

      _handle_notify = data.handle;
    } else if (0x7F == uuid->uuid[12]) {

      _handle_write = data.handle;
    }
  }

  return true;
}

// Connected or disconnected
boolean GATTS::onConnection(const LGATTAddress &addr, boolean connected) {
  _connected = connected;

  if (isDebug()) {

    APP_LOG("LGATTSUart::onConnection connected [%d], [%x:%x:%x:%x:%x:%x]", _connected, addr.addr[5], addr.addr[4], addr.addr[3], addr.addr[2], addr.addr[1], addr.addr[0]);
  }

  return true;
}

// Function for sending messages. It's called onRead because is the action that central device
// executes for reading data from peripheral
boolean GATTS::onRead(LGATTReadRequest &data) {

  if (isDebug()) {

    APP_LOG("LGATTSUart::onRead _connected [%d]", _connected);
  }

  if (_connected) {

    LGATTAttributeValue value = {0};
    const char *str = "";
    memcpy(value.value, str, strlen(str));
    value.len = strlen(str);

    if (isDebug()) {

      APP_LOG("LGATTSUart::onRead onRead [%d][%s]", value.len, value.value);
    }

    if (value.len > 0) {

      data.ackOK(value);
    } else {

      data.ackFail();
    }
  }

  return true;
}

// Function for receiving messages. It's called onWrite because is the action that central device
// executes for writing data in peripheral
boolean GATTS::onWrite(LGATTWriteRequest &data) {

  if (isDebug()) {

    APP_LOG("LGATTSUart::onWrite _connected [%d]", _connected);
  }

  if (_connected) {

    if (data.need_rsp) {

      LGATTAttributeValue value;
      value.len = 0;
      data.ackOK();
    }

    if (isDebug()) {

      APP_LOG("central data on peripheral rx[%s][%d]", data.value.value, data.value.len);
    }

    char* result = (char*)data.value.value;

    if (isDebug()) {

      Serial.println("Result:");
      Serial.println(result);
    }

    if (strstr(result, activateText) != NULL) {

      if (isDebug()) {

        Serial.println("Activate");
      }

      _serviceActivated = true;
    } else if (strstr(result, desactivateText) != NULL) {

      if (isDebug()) {

        Serial.println("Desactivate");
      }

      _serviceActivated = false;
    } else {

      if (isDebug()) {

        Serial.println("Error");
      }
    }
  }

  return true;
}

// Send string message to master -> Maximum 20 char (20 bytes)
boolean GATTS::sendMessage(const char *str) {

  if (strlen(str) > 20) {

    return false;
  } else {

    LGATTAttributeValue value = {0};
    value.len = strlen(str);
    memcpy(value.value, str, value.len);
    boolean ret = sendIndication(value, getHandleNotify(), false);

    if (!ret) {

      if (isDebug()) {

        APP_LOG("[FAILED] send [%d]", ret);
      }
    } else {

      if (isDebug()) {

        APP_LOG("send [%d][%s]", ret, str);
      }
    }

    return ret;
  }
}
