// Import classes and libraries
#include "ImportClasses.h"

// Variables
bool permissionForSendSMS = true;

// SMS text
String statusFromSMS = "status";
String textForStatusSMS = "My coordinates on map: ";
String textForStatusErrorSMS = "Sorry, my coordinates on map contain errors...";
String googleMapsURL = "https://www.google.com/maps/search/?api=1&query=";
String googleZoom = "&zoom=8";
String batteryFromSMS = "battery";
String textForBatterySMS = "Right now I have this battery percentage: ";
String feelFromSMS = "feel";
String textForFeelSMS = "I'm fine. Thank you very much! :)";
String resetFromSMS = "reset";
String textForResetSMS = "Wait, I'm restarting now...";
String textForResetSMSDisabled = "Sorry, this functionality is not in use yet...";
String activateFromSMS = "activate";
String textForActivateSMS = "Perfect! My location is active :)";
String desactivateFromSMS = "desactivate";
String textForDesactivateSMS = "Oops... Now my location is disabled :(";

// Public functions
void activateSIM() {

  while (!LSMS.ready()) {

    delay(100);
  }

  if (isDebug()) {

    Serial.println("Sim is activate ok");
  }
}

void sendSMSToPhoneNumber(char* phone, const String &textString) {

  if (permissionForSendSMS) {

    permissionForSendSMS = false;

    char toChar[100];
    textString.toCharArray(toChar, 100);
    char* text = toChar;

    LSMS.beginSMS(phone);
    LSMS.print(text);

    if (isDebug()) {

      Serial.println("Sending sms with status...");
    }

    if (LSMS.endSMS()) {

      if (isDebug()) {

        Serial.println("SMS send ok");
      }
    } else {

      if (isDebug()) {

        Serial.println("SMS send KO");
      }
    }

    if (LSMS.available()) {

      LSMS.flush();
    }
  }
}

void receivedSMS() {
  char bufer[20];
  int c;
  String message = "";

  if (LSMS.available()) {

    LSMS.remoteNumber(bufer, 20);

    if (isDebug()) {

      Serial.println("SMS received:");
      Serial.print("From phone number: ");
      Serial.println(bufer);
      Serial.print("Description: ");
    }

    while (true) {

      c = LSMS.read();

      if (c < 0) {

        break;
      }

      Serial.print((char)c);
      message += String((char)c);
    }

    if (isDebug()) {

      Serial.println();
      Serial.println("Message:");
      Serial.println(message);
    }

    permissionForSendSMS = true;

    if (message == statusFromSMS) {

      if (getLatitude() == "0.00000" || getLongitude() == "0.00000") {

        sendSMSToPhoneNumber(userPhone, textForStatusErrorSMS);
      } else {

        String textString = textForStatusSMS + googleMapsURL + getLatitude() + "," + getLongitude() + googleZoom;
        sendSMSToPhoneNumber(userPhone, textString);
      }
    } else if (message == batteryFromSMS) {

      String textString = textForBatterySMS + getBatteryLevel() + "%";
      sendSMSToPhoneNumber(userPhone, textString);
    } else if (message == activateFromSMS) {

      setServiceStatus(true);
      sendSMSToPhoneNumber(userPhone, textForActivateSMS);
    } else if (message == desactivateFromSMS) {

      setStatusToUpdateDataToOffUtil();
      setServiceStatus(false);
      sendSMSToPhoneNumber(userPhone, textForDesactivateSMS);
    } else if (message == feelFromSMS) {

      bool weather = getWeatherForMotorbikeLocation();

      if (weather) {

        sendSMSToPhoneNumber(userPhone, getFeel());
      } else {

        sendSMSToPhoneNumber(userPhone, textForFeelSMS);
      }
    } else if (message == resetFromSMS) {

      sendSMSToPhoneNumber(userPhone, textForResetSMS);
      resetByCode();
    }

    LSMS.flush();
  }
}
