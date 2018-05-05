/*
   MPU6050Utils class
   All functions for use MPU6050 module
*/

// Function for process all values from MPU6050 module
void processValuesFromMPU6050(int &pitch, int &roll, float &temperature);

// Set new values from MPU6050
void setSaveValuesFromMPU6050(const bool &newValue);
