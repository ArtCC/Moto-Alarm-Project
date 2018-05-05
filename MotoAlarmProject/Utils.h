/*
   Utils class
   All utils functions
*/

// Configure all services in init setup
void configureServices();

// Alarm is active, send data to server
void sendUserDataToServerForAlarmIsActive();

// Set service to enabled
void setStatusToUpdateDataToOnUtil();

// Set service to disabled
void setStatusToUpdateDataToOffUtil();

// Subscribe to services
void startSubscribeServices();

// Check if debug is active
bool isDebug();

// With weather, compose sms for motorbike feel
String getFeel();

// Reset app by code
void resetByCode();
