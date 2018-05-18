// Import classes and libraries
#include "ImportClasses.h"

// The type of data that we want to extract from the page
struct clientData {
  char token[250];
  char user_email[30];
  char user_nicename[30];
  char user_display_name[30];
};

// Skip HTTP headers so that we are at the beginning of the response's body
bool skipResponseHeaders(char endOfHeaders[]) {
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
void disconnect() {

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
}

bool readReponseContent(struct clientData* clientData) {
  const size_t bufferSize = JSON_OBJECT_SIZE(4);

  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {

    if (isDebug()) {

      Serial.println("JSON parsing failed!");
    }

    return false;
  }

  // Here were copy the strings we're interested in using to your struct data
  strcpy(clientData->token, root["token"]);
  strcpy(clientData->user_email, root["user_email"]);
  strcpy(clientData->user_nicename, root["user_nicename"]);
  strcpy(clientData->user_display_name, root["user_display_name"]);

  return true;
}

// Print the data extracted from the JSON
void printClientData(const struct clientData* clientData) {
  Serial.println("Response:");
  Serial.print("Token = ");
  Serial.println(clientData->token);
  Serial.print("User email = ");
  Serial.println(clientData->user_email);
  Serial.print("User nick name = ");
  Serial.println(clientData->user_nicename);
  Serial.print("User name = ");
  Serial.println(clientData->user_display_name);
}

bool sendRequestForToken() {

  if (client.connect(MAP_SERVER, port)) {

    String data = "{\"username\":" + userMail + "," + "\"password\":" + userPassword + "," + "\"exp\":" + "\"5\"" + "}";
    String thisLength = String(data.length());

    if (isDebug()) {

      Serial.println("Connected for get token");
      Serial.print("Connect to: ");
      Serial.println(MAP_SERVER);
    }

    client.print("POST /wp-json/jwt-auth/v1/token/");
    client.println(" HTTP/1.0");

    client.println("Content-Type: application/json; charset=UTF-8");
    client.println("Content-Length: " + thisLength);
    client.print("Host: ");
    client.println(MAP_SERVER);
    client.print("\n" + data);
    client.print(char(26));
    client.println("Connection: close");
    client.println();

    return true;
  }

  if (isDebug()) {

    Serial.println("sendRequestForToken: Connection failed");
  }

  return false;
}

// Public functions
bool requestForGetUserToken() {

  if (sendRequestForToken() && skipResponseHeaders("\r\n\r\n")) {

    clientData clientData;

    if (readReponseContent(&clientData)) {

      userToken = clientData.token;
      disconnect();

      if (isDebug()) {

        printClientData(&clientData);
      }

      return true;
    }
  }

  return false;
}

bool checkIfUserTokenExist() {
  unsigned int userTokenLength = userToken.length();

  if (userTokenLength > 1) {

    return true;
  }

  return false;
}

String getUserToken() {

  return headToken + userToken;
}
