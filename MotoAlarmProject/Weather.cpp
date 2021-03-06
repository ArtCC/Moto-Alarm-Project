// Import classes and libraries
#include "ImportClasses.h"

// Properties
#define WEATHER_BASE_URL "api.openweathermap.org"
String openWeatherAPIKey = "a708d82e019df78b5880aa93cf81fed9";
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

    if (debug) {

      Serial.println("No response or invalid response!");
    }

    return false;
  }

  return ok;
}

bool readReponseContent(struct weatherClientData* weatherClientData) {
  const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12);

  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {

    if (debug) {

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

  if (client.connect(WEATHER_BASE_URL, port)) {

    if (debug) {

      Serial.println("Connected for get weather");
      Serial.print("Connect to: ");
      Serial.println(WEATHER_BASE_URL);
    }

    String lat = "lat=" + getLatitude();
    String lon = "&lon=" + getLongitude();
    String apiKey = "&appid=" + openWeatherAPIKey;
    String units = "&units=metric";

    client.print("GET /data/2.5/weather?" + lat + lon + apiKey + units);
    client.println(" HTTP/1.0");
    client.print("Host: ");
    client.println(WEATHER_BASE_URL);
    client.println("Connection: close");
    client.println();

    if (debug) {

      Serial.println("Disconnecting");
    }

    return true;
  }

  if (debug) {

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

      if (debug) {

        Serial.println("Disconnecting");

        printclientDataForWeather(&weatherClientData);
      }

      client.stop();

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
