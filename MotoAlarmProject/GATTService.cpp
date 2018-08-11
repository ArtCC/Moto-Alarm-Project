// Import classes and libraries
#include "ImportClasses.h"
#include "GATTService.h"

// Has four characteristics
static LGATTServiceInfo g_serv1_decl[] = {
  {TYPE_SERVICE, "E30A39F4-73F5-4BC4-A12F-17D1AD07A962", TRUE, 0, 0, 0},
  {TYPE_CHARACTERISTIC, "01234567-89AB-CDEF-0123-456789ABCDF0", FALSE, VM_GATT_CHAR_PROP_READ, VM_GATT_PERM_READ, 0},
  {TYPE_CHARACTERISTIC, "01234567-89AB-CDEF-0123-456789ABCDF1", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0},
  {TYPE_END, 0, 0, 0, 0, 0}
};

// Prepare the data for profile
LGATTServiceInfo *GATTService::onLoadService(int32_t index) {

  if (debug) {

    Serial.printf("[GATTService]  onLoadService()\n");
    Serial.printf("    index : %08X\n", index);
  }

  return g_serv1_decl;
}

// Characteristic added
boolean GATTService::onCharacteristicAdded(LGATTAttributeData &data) {

  if (debug) {

    Serial.printf("[GATTService]  onCharacteristicAdded()\n");
    Serial.printf("    handle : %04X\n", data.handle);
    Serial.printf("    UUID   : %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n",
                  data.uuid[0xF], data.uuid[0xE], data.uuid[0xD], data.uuid[0xC],
                  data.uuid[0xB], data.uuid[0xA], data.uuid[0x9], data.uuid[0x8],
                  data.uuid[0x7], data.uuid[0x6], data.uuid[0x5], data.uuid[0x4],
                  data.uuid[0x3], data.uuid[0x2], data.uuid[0x1], data.uuid[0x0]);
    Serial.printf("    flag   : %d\n", data.failed );
  }

  if (!data.failed) {

    // Set handles here
  }

  return true;
}

// Connected or disconnected
boolean GATTService::onConnection(const LGATTAddress &addr, boolean connected) {

  if (debug) {

    Serial.printf("[GATTService] Client %X:%X:%X:%X:%X:%x ",
                  addr.addr[5], addr.addr[4], addr.addr[3], addr.addr[2], addr.addr[1], addr.addr[0]);

    if (connected) {

      Serial.println("[   connected]");
    } else {

      Serial.println("[disconnected]");
    }
  }

  // Set connection flag
  _connected = connected;

  return true;
}

// Read action comming from master
boolean GATTService::onRead(LGATTReadRequest &data) {

  if (debug) {

    Serial.println("[GATTService] onRead()");
  }

  if (_connected) {

    if (debug) {

      Serial.println("    Status         : Connected");
      Serial.printf("    Transaction ID : 0x%04X\n", data.trans_id);
      Serial.printf("    BT Address     : %X:%X:%X:%X:%X:%X\n",
                    data.bd.addr[5], data.bd.addr[4], data.bd.addr[3], data.bd.addr[2], data.bd.addr[1], data.bd.addr[0]);
      Serial.printf("    Attrib Handle  : 0x%04X\n", data.attr_handle);
      Serial.printf("    Offset         : 0x%04X\n", data.offset);
    }

    // Set Data
    LGATTAttributeValue value = { 0 };
    const char *str = "onRead send";
    memcpy(value.value, str, strlen(str));
    value.len = strlen(str);

    // Send Response
    data.ackOK(value);
  } else {

    if (debug) {

      // No connection
      Serial.println("    Status         : Disconnected");
    }
  }

  return true;
}

// Write action comming from master
boolean GATTService::onWrite(LGATTWriteRequest &data) {

  if (debug) {

    Serial.println("[GATTService]  onWrite()");
  }

  if (_connected) {

    if (debug) {

      Serial.printf("    Status         : Connected\n");
      Serial.printf("    Transaction ID : 0x%04X\n", data.trans_id);
      Serial.printf("    BT Address     : %02X:%02X:%02X:02X:%02X:%02X\n",
                    data.bd.addr[5], data.bd.addr[4], data.bd.addr[3], data.bd.addr[2], data.bd.addr[1], data.bd.addr[5]);
      Serial.printf("    Data Length    : %2d\n", data.value.len);
      Serial.printf("    Data (Hex)     : " );
    }

    for (uint16_t i = 0; i < data.value.len; i++) {

      if (debug) {

        Serial.printf("%02X ", data.value.value[i]);
      }
    }

    if (debug) {

      Serial.println();
      Serial.printf("    Data(ASCII)    : ");
    }

    String messageFromBluetooth = "";

    for (uint16_t i = 0; i < data.value.len; i++) {

      char message = data.value.value[i];
      messageFromBluetooth.concat(String(message));

      if (debug) {

        Serial.printf("%c", data.value.value[i]);
      }
    }

    if (debug) {

      Serial.println();
      Serial.printf("    Offset         : 0x%02X\n", data.offset);
      Serial.printf("    Need Response  : %s\n", (data.need_rsp) ? " True" : "False");

      Serial.println("Message received:");
      Serial.println(messageFromBluetooth);
      Serial.println();
      Serial.println();
    }

    bluetooth.receivedNewMessageFromBluetooth(messageFromBluetooth);
  }

  if (data.need_rsp) {

    data.ackOK();
  }

  return true;
}
