/*
   GPS class
   All functions for use GPS module
*/

// Activate GPS module
void activateGPS();

// Activate data from GPS module
bool activateGPSData();

// Get latitude value
String getLatitude();

// Get longitude value
String getLongitude();

// Get date time from GPS module
String getDateTime();

// Get velocity
float getVelocity();
