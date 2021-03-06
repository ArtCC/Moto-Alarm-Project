// Import classes and libraries
#include "ImportClasses.h"

// Properties
bool controlForSendingSMS = false;

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

    setStatusToUpdateDataToOnUtil();

    if (getLatitude() == "0.00000" || getLongitude() == "0.00000") {

      sendSMSToPhoneNumber(user.getUserPhone(), textForStatusErrorSMS);
    } else {

      if (activateGPSData()) {

        String textString = textForStatusSMS + googleMapsURL + getLatitude() + "," + getLongitude() + googleZoom;
        sendSMSToPhoneNumber(user.getUserPhone(), textString);
      } else {

        sendSMSToPhoneNumber(user.getUserPhone(), textForStatusErrorSMS);
      }
    }
  } else if (message == batteryFromSMS || message == batteryWatchFromSMS) {

    String textString = textForBatterySMS + getBatteryLevel() + "%";
    sendSMSToPhoneNumber(user.getUserPhone(), textString);
  } else if (message == activateFromSMS || message == activateWatchFromSMS) {

    setServiceStatus(true);
    sendSMSToPhoneNumber(user.getUserPhone(), textForActivateSMS);

    // Send user data to server
    setStatusToUpdateDataToOnUtil();
  } else if (message == desactivateFromSMS || message == desactivateWatchFromSMS) {

    setServiceStatus(false);
    gyroscope.setAlarmIsActive(false);
    sendSMSToPhoneNumber(user.getUserPhone(), textForDesactivateSMS);

    // Not update user data but send disable service
    setStatusToUpdateDataToOffUtil(false);
  } else if (message == feelFromSMS || message == feelWatchFromSMS) {

    bool weather = getWeatherForMotorbikeLocation();

    if (weather) {

      sendSMSToPhoneNumber(user.getUserPhone(), getFeel());
    } else {

      sendSMSToPhoneNumber(user.getUserPhone(), textForFeelSMS);
    }
  } else if (message == resetFromSMS || message == resetWatchFromSMS) {

    sendSMSToPhoneNumber(user.getUserPhone(), textForResetSMS);
    resetByCode();
  }
}

// Public functions
void activateSIM() {

  while (!LSMS.ready()) {

    delay(100);
  }

  if (debug) {

    Serial.println("Sim is activate ok");
  }

  if (LSMS.available()) {

    LSMS.flush();
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

    if (debug) {

      Serial.println("SMS received:");
      Serial.print("From phone number: ");
      Serial.println(bufer);
      Serial.print("Description: ");
      Serial.println();
      Serial.println("Message:");
      Serial.println(message);
    }

    LSMS.flush();

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

      if (message == statusFromSMS) {

        setStatusToUpdateDataToOnUtil();

        if (getLatitude() == "0.00000" || getLongitude() == "0.00000") {

          sendSMSToPhoneNumber(user.getUserPhone(), textForStatusErrorSMS);
        } else {

          if (activateGPSData()) {

            String textString = textForStatusSMS + googleMapsURL + getLatitude() + "," + getLongitude() + googleZoom;
            sendSMSToPhoneNumber(user.getUserPhone(), textString);
          } else {

            sendSMSToPhoneNumber(user.getUserPhone(), textForStatusErrorSMS);
          }
        }
      } else if (message == batteryFromSMS) {

        String message = "\"" + textForBatterySMS + getBatteryLevel() + "%" + "\"";
        String data = "{\"message_chat\":" + message + "}";

        setPOSTRequest(data);
      } else if (message == activateFromSMS) {

        String message = "\"" + textForActivateSMS + "\"";
        String data = "{\"message_chat\":" + message + "}";

        setPOSTRequest(data);

        setServiceStatus(true);

        // Send user data to server
        setStatusToUpdateDataToOnUtil();
      } else if (message == desactivateFromSMS) {

        String message = "\"" + textForDesactivateSMS + "\"";
        String data = "{\"message_chat\":" + message + "}";

        setPOSTRequest(data);

        setServiceStatus(false);
        gyroscope.setAlarmIsActive(false);

        // Not update user data but send disable service
        setStatusToUpdateDataToOffUtil(false);
      } else if (message == feelFromSMS) {

        bool weather = getWeatherForMotorbikeLocation();

        if (weather) {

          String message = "\"" + getFeel() + "\"";
          String data = "{\"message_chat\":" + message + "}";

          setPOSTRequest(data);
        } else {

          sendSMSToPhoneNumber(user.getUserPhone(), textForFeelSMS);
        }
      } else if (message == resetFromSMS) {

        String message = "\"" + textForResetSMS + "\"";
        String data = "{\"message_chat\":" + message + "}";

        setPOSTRequest(data);

        resetByCode();
      }
    }
  }
}

void sendSMSToPhoneNumber(const String &phone, const String &textString) {

  if (!controlForSendingSMS) {

    if (LSMS.available()) {

      LSMS.flush();
    }

    controlForSendingSMS = true;

    String phoneClean = phone;
    phoneClean.trim();

    if (debug) {

      Serial.println("Phone:");
      Serial.println(phoneClean);
      Serial.println("Text:");
      Serial.println(textString);
    }

    char convertPhone[15];
    phoneClean.toCharArray(convertPhone, 15);
    char *finalPhone = convertPhone;

    char toChar[100];
    textString.toCharArray(toChar, 100);
    char *text = toChar;

    LSMS.beginSMS(finalPhone);
    LSMS.print(text);

    if (debug) {

      Serial.println("Sending sms with status...");
    }

    if (LSMS.endSMS()) {

      if (debug) {

        Serial.println("SMS send ok");
      }
    } else {

      if (debug) {

        Serial.println("SMS send KO");
      }
    }

    controlForSendingSMS = false;
  }
}
