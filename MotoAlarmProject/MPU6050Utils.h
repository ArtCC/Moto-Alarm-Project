/*
   MPU6050Utils class
   All functions for use MPU6050 module
*/

// Function for process all values from MPU6050 module
void processValuesFromMPU6050(int &pitch, int &roll, float &temperature);

// Function for set new values from MPU6050
void setSaveValuesFromMPU6050(const bool &newValue);

// Function for get value for alarm active or not
bool getIfAlarmIsActive();
