// Import classes and libraries
#include "ImportClasses.h"

// Public util functions
void setPOSTRequest(String &path) {

  if (client.connect(MAP_SERVER, port)) {

    if (isDebug()) {

      Serial.println("Success");
      Serial.print("Connect to: ");
      Serial.println(MAP_SERVER);
      Serial.println("Connected");
      Serial.println("Path:");
      Serial.println(path);
    }

    String thisLength = String(path.length());

    client.print("POST /wp-json/wp/v2/users/" + userId);
    client.println(" HTTP/1.1");
    client.println("Content-Type: application/json; charset=UTF-8");
    client.println("Content-Length: " + thisLength);
    client.print("Host: ");
    client.println(MAP_SERVER);
    client.println("Authorization: " + getUserToken());
    client.print("\n" + path);
    client.print(char(26));
    client.println("Connection: close");
    client.println();

    if (isDebug()) {

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

    if (isDebug()) {

      Serial.println("setPOSTRequest: Connection failed");
    }

    client.stop();
  }
}

void setUpdateDataUserToServer(const String &latitude, const String &longitude, const String &batteryLevel, const String &batteryStatus) {

  if (client.connect(MAP_SERVER, port)) {

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

    if (isDebug()) {

      Serial.println("Updating user data in server...");
    }

    setPOSTRequest(data);
  } else {

    if (isDebug()) {

      Serial.println("setUpdateDataUserToServer: Connection failed");
    }

    client.stop();
  }
}

void setStatusToUpdateDataToOff(const String &batteryLevel, const String &batteryStatus, const bool &gpsError) {

  if (client.connect(MAP_SERVER, port)) {

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

    if (isDebug()) {

      Serial.println("Not send gps info to server...");
    }

    setPOSTRequest(data);
  } else {

    if (isDebug()) {

      Serial.println("setStatusToUpdateDataToOff : Connection failed");
    }

    client.stop();
  }
}
