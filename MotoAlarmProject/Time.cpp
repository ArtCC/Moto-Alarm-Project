// Import classes and libraries
#include "ImportClasses.h"

// Variables
String updateTime;

// The type of data that we want to extract from the page
struct userData {
  char deviceUpdateTime[10];
};

// Skip HTTP headers so that we are at the beginning of the response's body
bool skipResponseHeadersForTime(char endOfHeaders[]) {
  // HTTP headers end with an empty line
  client.setTimeout(HTTP_TIMEOUT);
  bool ok = client.find(endOfHeaders);

  if (!ok) {

    if (isDebug()) {

      Serial.println("No response or invalid response!");
    }

    return false;
  }

  return ok;
}

// Close the connection with the HTTP server
void disconnectForTime() {

  if (isDebug()) {

    Serial.println("Disconnect");
  }

  client.stop();
}

bool readReponseContentForTime(struct userData* userData) {
  const size_t bufferSize = JSON_ARRAY_SIZE(0) + 2 * JSON_ARRAY_SIZE(1) + 2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(35);

  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {

    if (isDebug()) {

      Serial.println("JSON parsing failed!");
    }

    return false;
  }

  // Here were copy the strings we're interested in using to your struct data
  strcpy(userData->deviceUpdateTime, root["device_update_time"]);

  return true;
}

// Print the data extracted from the JSON
void printUserData(const struct userData* userData) {
  Serial.println("Response:");
  Serial.print("Device update time = ");
  Serial.println(userData->deviceUpdateTime);
}

bool sendRequestForTime() {

  if (client.connect(server, port)) {

    if (isDebug()) {

      Serial.println("Connected for get device update time");
      Serial.print("Connect to: ");
      Serial.println(server);
    }

    client.print("GET /wp-json/wp/v2/users/" + userId);
    client.println(" HTTP/1.0");
    client.print("Host: ");
    client.println(server);
    client.println("Authorization: " + getUserToken());
    client.println("Connection: close");
    client.println();

    return true;
  }

  if (isDebug()) {

    Serial.println("sendRequestForTime: Connection failed");
  }

  return false;
}

// Public functions
bool getDeviceUpdateTime() {

  if (sendRequestForTime() && skipResponseHeadersForTime("\r\n\r\n")) {

    userData userData;

    if (readReponseContentForTime(&userData)) {

      updateTime = userData.deviceUpdateTime;
      disconnectForTime();

      if (isDebug()) {

        printUserData(&userData);
      }

      return true;
    } else {

      updateTime = "1800000";

      return true;
    }
  }

  return false;
}

long getValueForDeviceUpdateTime() {
  long updateTimeInLong = updateTime.toInt();

  return updateTimeInLong;
}
