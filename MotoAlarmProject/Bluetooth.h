/*
   Bluetooth class
   All functions for use bluetooth module
*/

// Activate bluetooth module
void activateBluetoothModule();

// Subscribe to events to bluetooth module
void subscribeToEventsBluetoothModule();

// Check if connection is active
bool uartIsActive();

// Check if service is active or not
bool serviceIsActiveForSendDataToService();

// Change status for service variable
void setServiceStatus(const bool &newStatus);

// Send info with bluetooth module
void sendInfoWithBluetoothModule(char* text);
