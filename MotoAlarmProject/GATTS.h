// Import classes and libraries
#include "LGATTServer.h"

// Variables
#ifndef __GATT_UART_H__
#define __GATT_UART_H__

class GATTS : public LGATTService {
  public:
    uint16_t getHandle(int32_t type);

    boolean isConnected() {

      return _connected;
    };

    boolean isServiceActive() {

      return _serviceActivated;
    }

    void setServiceStatusInGATTS(bool &newStatus) {
      _serviceActivated = newStatus;
    }

    uint16_t getHandleNotify() {

      return _handle_notify;
    };

    boolean sendMessage(const char *str);

    // Status for service
    bool _serviceActivated;
  protected:
    // Prepare the data for profile
    virtual LGATTServiceInfo *onLoadService(int32_t index);
    // Characteristic added
    virtual boolean onCharacteristicAdded(LGATTAttributeData &data);
    // Connected or disconnected
    virtual boolean onConnection(const LGATTAddress &addr, boolean connected);
    // Read action comming from master
    virtual boolean onRead(LGATTReadRequest &data);
    // Write action comming from master
    virtual boolean onWrite(LGATTWriteRequest &data);
  private:
    enum TypeMessage {Life_Info, Device_Info};
    uint16_t _handle_notify;
    uint16_t _handle_write;
    boolean _connected;
};
#endif
