/*
   GyroscopeUtils class
   All functions for use Grove 6-Axis Accelerometer & Gyroscope module
*/

// Function for get value for alarm active or not
bool getIfAlarmIsActive();

// Function for set alarm status
void setAlarmIsActive(const bool &newValue);

// Function for set new values from module
void setSaveValuesFromGroveSensor(const bool &newValue);

// Function for process all values from module
void processValuesFromGroveSensor(float aX,
                                  float aY,
                                  float aZ,
                                  float gX,
                                  float gY,
                                  float gZ,
                                  float temperature);
