/*
   GPRS class
   All functions for use GPRS module
*/

// Send request to server
void setPOSTRequest(String &path);

// Check if connection is enabled
bool getStatusCorrectConnection();

// Connect to internet with GPRS and send data to server
void setUpdateDataUserToServer(const String &latitude, const String &longitude, const String &batteryLevel, const String &batteryStatus);

// Connect to internet with GPRS and set to off to update data for user in web server
void setStatusToUpdateDataToOff(const String &batteryLevel, const String &batteryStatus);
