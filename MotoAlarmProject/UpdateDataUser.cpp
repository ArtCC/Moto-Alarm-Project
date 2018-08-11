// Import classes and libraries
#include "ImportClasses.h"

// Public util functions
void setPOSTRequest(String &path) {

  if (client.connect(mapServer, port)) {

    String thisLength = String(path.length());
    String token = "Authorization: " + user.getUserToken();
    String postPathWithUserId = "POST /wp-json/wp/v2/users/" + user.getUserId();

    if (debug) {

      Serial.println("Success");
      Serial.print("Connect to: ");
      Serial.println(mapServer);
      Serial.println("Connected");
      Serial.println("Path:");
      Serial.println(path);
      Serial.println("Token:");
      Serial.println(token);
      Serial.println("User id:");
      Serial.println(postPathWithUserId);
    }

    client.print(postPathWithUserId);
    client.println(" HTTP/1.1");
    client.println("Content-Type: application/json; charset=UTF-8");
    client.println("Content-Length: " + thisLength);
    client.print("Host: ");
    client.println(mapServer);
    client.println(token);
    client.print("\n" + path);
    client.print(char(26));
    client.println("Connection: close");
    client.println();

    if (debug) {

      while (client.connected()) {

        if (client.available()) {

          char str = client.read();
          Serial.print(str);
        }
      }

      Serial.println("Disconnecting");
    }

    client.stop();
  } else {

    if (debug) {

      Serial.println("setPOSTRequest: Connection failed");
    }
  }
}

void setUpdateDataUserToServer(const String &latitude, const String &longitude, const String &batteryLevel, const String &batteryStatus) {
  String sendDataStatus = "\"true\"";

  if (LBattery.level() <= 3) {

    sendDataStatus = "\"false\"";
  }

  String lat = "\"" + latitude + "\"";
  String lon = "\"" + longitude + "\"";
  String dateTime = "\"" + getDateTime() + "\"";
  String bLevel = "\"" + batteryLevel + "\"";
  String bStatus = "\"" + batteryStatus + "\"";
  String velocity = "\"" + String(getVelocity()) + "\"";
  String gpsStatus = "\"false\"";

  String data = "{\"motorbike_latitude\":" + lat + "," +
                "\"motorbike_longitude\":" + lon + "," +
                "\"motorbike_date_last_position\":" + dateTime + "," +
                "\"activated_motorbike_position\":" + sendDataStatus + "," +
                "\"battery_motorbike_device\":" + bLevel + "," +
                "\"battery_motorbike_status_charging\":" + bStatus + "," +
                "\"motorbike_velocity\":" + velocity + "," +
                "\"gps_error\":" + gpsStatus +
                "}";

  if (debug) {

    Serial.println("Updating user data in server...");
  }

  setPOSTRequest(data);
}

void setStatusToUpdateDataToOff(const String &batteryLevel, const String &batteryStatus, const bool &gpsError) {
  String sendDataStatus = "\"false\"";
  String bLevel = "\"" + batteryLevel + "\"";
  String bStatus = "\"" + batteryStatus + "\"";

  String gpsErrorValue = "false";

  if (gpsError == true) {

    gpsErrorValue = "true";
  }

  String gpsStatus = "\"" + gpsErrorValue + "\"";

  String data = "{\"activated_motorbike_position\":" + sendDataStatus + "," +
                "\"battery_motorbike_device\":" + bLevel + "," +
                "\"battery_motorbike_status_charging\":" + bStatus + "," +
                "\"gps_error\":" + gpsStatus +
                "}";

  if (debug) {

    Serial.println("Not send gps info to server...");
  }

  setPOSTRequest(data);
}
