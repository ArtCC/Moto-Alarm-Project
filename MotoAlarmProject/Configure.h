/*
   Configure class
   All functions for configure all modules in init
*/

// Configure all services in init setup
void configureServices();

// Subscribe to services
void startSubscribeServices();

// Check status service and activated or desactivated
void checkStatusService();

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
