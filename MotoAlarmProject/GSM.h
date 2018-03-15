/*
   GSM class
   All functions for use GSM module
*/

// Activate GSM module and SIM
void activateSIM();

// Send SMS to phone number
void sendSMSToPhoneNumber(char* phone, const String &textString);

// Callback for received SMS from external service
void receivedSMS();
