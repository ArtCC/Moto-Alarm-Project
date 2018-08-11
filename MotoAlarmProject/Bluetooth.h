/*
   Bluetooth class
   All functions for use bluetooth module
*/

class Bluetooth {
  private:

    String temporalUserToken = "Bearer ";
  public:

    // Activate bluetooth module
    void activateBluetoothModule();

    // Process new message from bluetooth connection
    void receivedNewMessageFromBluetooth(String &message);

    // Subscribe to events to bluetooth module
    void subscribeToEventsBluetoothModule();
};
