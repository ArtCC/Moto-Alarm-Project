/*
   Utils class
   All utils functions
*/

// Function for request get token and get update device time fro server
void configureForFirstInit();

// Config GPRS
void configureGPRSConnection();

// Config WiFi
void configureWiFi();

// Configure all services in init setup
void configureServices();

// Alarm is active, send data to server
void sendUserDataToServerForAlarmIsActive();

// Set service to enabled
void setStatusToUpdateDataToOnUtil();

// Set service to disabled
void setStatusToUpdateDataToOffUtil(const bool &gpsError);

// Subscribe to services
void startSubscribeServices();

// Start services for detection and send request
void startAllServices();

// Check if debug is active
bool isDebug();

// With weather, compose sms for motorbike feel
String getFeel();

// Reset app by code
void resetByCode();
