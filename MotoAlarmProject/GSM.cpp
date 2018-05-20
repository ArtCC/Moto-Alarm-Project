// Import classes and libraries
#include "ImportClasses.h"

// Properties
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

      sendSMSToPhoneNumber(getUserPhone(), textForStatusErrorSMS);
    } else {

      String textString = textForStatusSMS + googleMapsURL + getLatitude() + "," + getLongitude() + googleZoom;
      sendSMSToPhoneNumber(getUserPhone(), textString);
    }
  } else if (message == batteryFromSMS || message == batteryWatchFromSMS) {

    String textString = textForBatterySMS + getBatteryLevel() + "%";
    sendSMSToPhoneNumber(getUserPhone(), textString);
  } else if (message == activateFromSMS || message == activateWatchFromSMS) {

    setServiceStatus(true);
    sendSMSToPhoneNumber(getUserPhone(), textForActivateSMS);

    // Send user data to server
    setStatusToUpdateDataToOnUtil();
  } else if (message == desactivateFromSMS || message == desactivateWatchFromSMS) {

    setServiceStatus(false);
    sendSMSToPhoneNumber(getUserPhone(), textForDesactivateSMS);

    // Not update user data but send disable service
    setStatusToUpdateDataToOffUtil(false);
  } else if (message == feelFromSMS || message == feelWatchFromSMS) {

    bool weather = getWeatherForMotorbikeLocation();

    if (weather) {

      sendSMSToPhoneNumber(getUserPhone(), getFeel());
    } else {

      sendSMSToPhoneNumber(getUserPhone(), textForFeelSMS);
    }
  } else if (message == resetFromSMS || message == resetWatchFromSMS) {

    sendSMSToPhoneNumber(getUserPhone(), textForResetSMS);
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

    if (LSMS.available()) {

      LSMS.flush();
    }

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

        if (getLatitude() == "0.00000" || getLongitude() == "0.00000") {

          sendSMSToPhoneNumber(getUserPhone(), textForStatusErrorSMS);
        } else {

          String textString = textForStatusSMS + googleMapsURL + getLatitude() + "," + getLongitude() + googleZoom;
          sendSMSToPhoneNumber(getUserPhone(), textString);
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

        // Not update user data but send disable service
        setStatusToUpdateDataToOffUtil(false);
      } else if (message == feelFromSMS) {

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
  char convertPhone[15];
  phone.toCharArray(convertPhone, 15);
  char *finalPhone = convertPhone;

  Serial.println("");
  Serial.println("Phone:");
  Serial.println(phone);
  Serial.println("Final phone:");
  Serial.println(finalPhone);
  Serial.println("");

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

  if (LSMS.available()) {

    LSMS.flush();
  }
}
