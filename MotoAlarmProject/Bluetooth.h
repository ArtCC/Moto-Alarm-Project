/*
   Bluetooth class
   All functions for use bluetooth module
*/

// Activate bluetooth module
void activateBluetoothModule();

// Subscribe to events to bluetooth module
void subscribeToEventsBluetoothModule();

// Process new message from bluetooth connection
void receivedNewMessageFromBluetooth(String &message);
