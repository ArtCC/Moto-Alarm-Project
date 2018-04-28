/*
   UpdateDataUser class
   All functions for update data user in server
*/

// Send request to server
void setPOSTRequest(String &path);

// Connect to internet with GPRS and send data to server
void setUpdateDataUserToServer(const String &latitude, const String &longitude, const String &batteryLevel, const String &batteryStatus);

// Connect to internet with GPRS and set to off to update data for user in web server
void setStatusToUpdateDataToOff(const String &batteryLevel, const String &batteryStatus);
