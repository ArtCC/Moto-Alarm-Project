/*
   Bluetooth class
   All functions for use bluetooth module
*/

// Activate bluetooth module
void activateBluetoothModule();

// Process new message from bluetooth connection
void receivedNewMessageFromBluetooth(String &message);

// Subscribe to events to bluetooth module
void subscribeToEventsBluetoothModule();
