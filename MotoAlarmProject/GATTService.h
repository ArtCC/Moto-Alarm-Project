/*
   GATT class
   All functions for configure bluetooth server
*/

#include <LGATTUUID.h>
#include "LGATTServer.h"

#ifndef __LGATT_BATT_H__
#define __LGATT_BATTT_H__

class GATTService : public LGATTService {
  public:
    boolean isConnected() {

      return _connected;
    };

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
    boolean _connected;
};

#endif
