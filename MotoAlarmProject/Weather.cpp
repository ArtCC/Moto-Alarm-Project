// Import classes and libraries
#include "ImportClasses.h"

// Variables
char weatherBaseUrl[] = "api.openweathermap.org";
String openWeatherAPIKey = "7361a32159627d3d34db82854a569bf7";
String weatherTitleString = "";
String cityString = "";
String temperatureString = "";
String humidityString = "";

// The type of data that we want to extract from the page
struct weatherClientData {
  char weatherTitle[25];
  char city[25];
  char temperature[5];
  char humidity[5];
};

// Private functions
// Skip HTTP headers so that we are at the beginning of the response's body
bool skipResponseHeadersForWeather(char endOfHeaders[]) {
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
void disconnectForWeather() {

  if (isDebug()) {

    while (client.connected()) {

      if ( client.available()) {

        char str = client.read();
        Serial.print(str);
      }
    }

    Serial.println("Disconnecting");
  }

  client.stop();
}

bool readReponseContent(struct weatherClientData* weatherClientData) {
  const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12);

  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {

    if (isDebug()) {

      Serial.println("JSON parsing failed!");
    }

    return false;
  }

  // Here were copy the strings we're interested in using to your struct data
  strcpy(weatherClientData->weatherTitle, root["weather"][0]["main"]);
  strcpy(weatherClientData->city, root["name"]);
  strcpy(weatherClientData->temperature, root["main"]["temp"]);
  strcpy(weatherClientData->humidity, root["main"]["humidity"]);

  return true;
}

// Print the data extracted from the JSON
void printclientDataForWeather(const struct weatherClientData* weatherClientData) {
  Serial.println("Response:");
  Serial.print("Weather title = ");
  Serial.println(weatherClientData->weatherTitle);
  Serial.print("Weather city = ");
  Serial.println(weatherClientData->city);
  Serial.print("Weather temperature = ");
  Serial.println(weatherClientData->temperature);
  Serial.print("Weather humidity = ");
  Serial.println(weatherClientData->humidity);
}

bool sendRequestForWeatherForMotorbikeLocation() {

  if (client.connect(weatherBaseUrl, port)) {

    if (isDebug()) {

      Serial.println("Connected for get weather");
      Serial.print("Connect to: ");
      Serial.println(weatherBaseUrl);
    }

    String lat = "lat=" + getLatitude();
    String lon = "&lon=" + getLongitude();
    String apiKey = "&appid=" + openWeatherAPIKey;
    String units = "&units=metric";

    client.print("GET /data/2.5/weather?" + lat + lon + apiKey + units);
    client.println(" HTTP/1.0");
    client.print("Host: ");
    client.println(weatherBaseUrl);
    client.println("Connection: close");
    client.println();

    if (isDebug()) {

      Serial.println("Disconnecting");
    }

    return true;
  }

  if (isDebug()) {

    Serial.println("getWeatherForMotorbikeLocation: Connection failed");
  }

  return false;
}

// Public functions
bool getWeatherForMotorbikeLocation() {

  if (sendRequestForWeatherForMotorbikeLocation() && skipResponseHeadersForWeather("\r\n\r\n")) {

    weatherClientData weatherClientData;

    if (readReponseContent(&weatherClientData)) {

      weatherTitleString = weatherClientData.weatherTitle;
      cityString = weatherClientData.city;
      temperatureString = weatherClientData.temperature;
      humidityString = weatherClientData.humidity;

      disconnectForWeather();

      if (isDebug()) {

        printclientDataForWeather(&weatherClientData);
      }

      return true;
    }
  }

  return false;
}

String getWeatherTitle() {

  return weatherTitleString;
}

String getCity() {

  return cityString;
}

String getTemp() {

  return temperatureString;
}

String getHumidity() {

  return humidityString;
}
