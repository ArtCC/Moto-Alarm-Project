/*
   Configure class
   All functions for configure all modules in init
*/

// Configure all services in init setup
void configureServices();

// Subscribe to services
void startSubscribeServices();

// Start services for detection and send request
void startAllServices();

// Send request with stop services
void stopServices();

// Set service to enabled
void setStatusToUpdateDataToOnUtil();

// Set service to disabled
void setStatusToUpdateDataToOffUtil(const bool &gpsError);

// Change status for service
void setServiceStatus(const bool &value);

// Get service status
bool getServiceStatus();

// With weather, compose sms for motorbike feel
String getFeel();

// Reset app by code
void resetByCode();

// Set user token
void setUserToken(String &string);

// Set user id
void setUserId(String &string);

// Set user phone
void setUserPhone(String &string);

// Get user token
String getUserToken();

// Get user id
String getUserId();

// Get user phone
String getUserPhone();

// Set apn name
void setAPNName(String &string);

// Set apn user
void setAPNUser(String &string);

// Set apn password
void setAPNPassword(String &string);

// Set device name
void setDeviceNameForBluetooth(String &string);

// Get apn name
String getAPNName();

// Get apn user
String getAPNUser();

// Get apn password
String getAPNPassword();

// Get device name
String getDeviceNameForBluetooth();
