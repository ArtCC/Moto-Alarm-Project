// Import classes and libraries
#include "ImportClasses.h"

// Variables
bool permissionForSendSMS = true;

// SMS text
String statusFromSMS = "status";
String batteryFromSMS = "battery";
String feelFromSMS = "feel";
String resetFromSMS = "reset";
String activateFromSMS = "activate";
String desactivateFromSMS = "desactivate";
String googleMapsURL = "https://www.google.com/maps/search/?api=1&query=";
String googleZoom = "&zoom=8";

// SMS text from Apple Watch
String statusWatchFromSMS = "status.watch";
String batteryWatchFromSMS = "battery.watch";
String feelWatchFromSMS = "feel.watch";
String resetWatchFromSMS = "reset.watch";
String activateWatchFromSMS = "activate.watch";
String desactivateWatchFromSMS = "desactivate.watch";
String deviceUpdateTimeWatchFromSMS = "update.time.watch";

// Private functions
void sendMessage(String &message) {

  if (message == statusFromSMS || message == statusWatchFromSMS) {

    if (getLatitude() == "0.00000" || getLongitude() == "0.00000") {

      sendSMSToPhoneNumber(userPhone, textForStatusErrorSMS);
    } else {

      String textString = textForStatusSMS + googleMapsURL + getLatitude() + "," + getLongitude() + googleZoom;
      sendSMSToPhoneNumber(userPhone, textString);
    }
  } else if (message == batteryFromSMS || message == batteryWatchFromSMS) {

    String textString = textForBatterySMS + getBatteryLevel() + "%";
    sendSMSToPhoneNumber(userPhone, textString);
  } else if (message == activateFromSMS || message == activateWatchFromSMS) {

    setStatusToUpdateDataToOnUtil();
    setServiceStatus(true);
    sendSMSToPhoneNumber(userPhone, textForActivateSMS);
  } else if (message == desactivateFromSMS || message == desactivateWatchFromSMS) {

    setStatusToUpdateDataToOffUtil();
    setServiceStatus(false);
    sendSMSToPhoneNumber(userPhone, textForDesactivateSMS);
  } else if (message == feelFromSMS || message == feelWatchFromSMS) {

    if (getStatusCorrectConnection()) {

      bool weather = getWeatherForMotorbikeLocation();

      if (weather) {

        sendSMSToPhoneNumber(userPhone, getFeel());
      } else {

        sendSMSToPhoneNumber(userPhone, textForFeelSMS);
      }
    }
  } else if (message == resetFromSMS || message == resetWatchFromSMS) {

    sendSMSToPhoneNumber(userPhone, textForResetSMS);
    resetByCode();
  }
}

// Public functions
void activateSIM() {

  while (!LSMS.ready()) {

    delay(100);
  }

  if (isDebug()) {

    Serial.println("Sim is activate ok");
  }

  if (LSMS.available()) {

    LSMS.flush();
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

    while (true) {

      c = LSMS.read();

      if (c < 0) {

        break;
      }

      Serial.print((char)c);
      message += String((char)c);
    }

    if (isDebug()) {

      Serial.println("SMS received:");
      Serial.print("From phone number: ");
      Serial.println(bufer);
      Serial.print("Description: ");
      Serial.println();
      Serial.println("Message:");
      Serial.println(message);
    }

    if (LSMS.available()) {

      LSMS.flush();
    }

    permissionForSendSMS = true;

    if (message == statusWatchFromSMS ||
        message == batteryWatchFromSMS ||
        message == activateWatchFromSMS ||
        message == desactivateWatchFromSMS ||
        message == feelWatchFromSMS ||
        message == resetWatchFromSMS) {

      sendMessage(message);
    } else if (message == deviceUpdateTimeWatchFromSMS) {

      resetByCode();
    } else {

      if (getStatusCorrectConnection()) {

        if (message == statusFromSMS) {

          if (getLatitude() == "0.00000" || getLongitude() == "0.00000") {

            sendSMSToPhoneNumber(userPhone, textForStatusErrorSMS);
          } else {

            String textString = textForStatusSMS + googleMapsURL + getLatitude() + "," + getLongitude() + googleZoom;
            sendSMSToPhoneNumber(userPhone, textString);
          }
        } else if (message == batteryFromSMS) {

          String message = "\"" + textForBatterySMS + getBatteryLevel() + "%" + "\"";
          String data = "{\"message_chat\":" + message + "}";

          setPOSTRequest(data);
        } else if (message == activateFromSMS) {

          String message = "\"" + textForActivateSMS + "\"";
          String data = "{\"message_chat\":" + message + "}";

          setPOSTRequest(data);

          setStatusToUpdateDataToOnUtil();
          setServiceStatus(true);
        } else if (message == desactivateFromSMS) {

          String message = "\"" + textForDesactivateSMS + "\"";
          String data = "{\"message_chat\":" + message + "}";

          setPOSTRequest(data);

          setStatusToUpdateDataToOffUtil();
          setServiceStatus(false);
        } else if (message == feelFromSMS) {

          if (getStatusCorrectConnection()) {

            bool weather = getWeatherForMotorbikeLocation();

            if (weather) {

              String message = "\"" + getFeel() + "\"";
              String data = "{\"message_chat\":" + message + "}";

              setPOSTRequest(data);
            } else {

              String message = "\"" + textForFeelSMS + "\"";
              String data = "{\"message_chat\":" + message + "}";

              setPOSTRequest(data);
            }
          }
        } else if (message == resetFromSMS) {

          String message = "\"" + textForResetSMS + "\"";
          String data = "{\"message_chat\":" + message + "}";

          setPOSTRequest(data);

          resetByCode();
        }
      } else {

        sendMessage(message);
      }
    }
  }
}
