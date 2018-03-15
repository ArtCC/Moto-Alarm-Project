// Import classes and libraries
#include "ImportClasses.h"

// Variables
gpsSentenceInfoStruct info; // Needed to get GPS data

double latitude = 0.000000;
double longitude = 0.000000;

float altitude = 0.00;
float dop = 100.00; // Dilution of precision
float geoid = 0.00;
float k_speed = 0.00, m_speed = 0.00; // Speed in knots and speed in m/s
float track_angle = 0.00;

int fix = 0;
int hour = 0, minute = 0, second = 0;
int sat_num = 0; // Number of visible satellites
int day = 0, month = 0, year = 0;

String time_format = "00:00:00", date_format = "00:00:0000";
String old_time_and_date_format = "00:00:00,00:00:0000";
String lat_format = "0.00000", lon_format = "0.00000";
String old_lat_format = "0.00000", old_lon_format = "0.00000";
float velocity = 0.00;

// Private util functions
/**
  Converts degrees from (d)ddmm.mmmm to (d)dd.mmmmmm
  @param str the string rappresentation of the angle in (d)ddmm.mmmm format
  @param dir if true the direction is south, and the angle is negative.
  @return the given angle in dd.mmmmmm format.
*/
float convert(String str, boolean dir) {
  double mm, dd;
  int point = str.indexOf('.');
  dd = str.substring(0, (point - 2)).toFloat();
  mm = str.substring(point - 2).toFloat() / 60.00;

  return (dir ? -1 : 1) * (dd + mm);
}

/**
  Gets gps informations
  @param info gpsSentenceInfoStruct is a struct containing NMEA sentence infomation
  @return the number of hooked satellites, or 0 if there was an error getting informations
*/
int getData(gpsSentenceInfoStruct* info) {

  if (isDebug()) {

    Serial.println("Collecting GPS data");
  }

  LGPS.getData(info);

  if (isDebug()) {

    Serial.println((char*)info->GPGGA);
  }

  if (info->GPGGA[0] == '$') {

    if (isDebug()) {

      Serial.print("Parsing GGA data...");
    }

    String str = (char*)(info->GPGGA);
    str = str.substring(str.indexOf(',') + 1);
    hour = str.substring(0, 2).toInt();
    minute = str.substring(2, 4).toInt();
    second = str.substring(4, 6).toInt();
    time_format = "";
    time_format += hour;
    time_format += ":";
    time_format += minute;
    time_format += ":";
    time_format += second;
    str = str.substring(str.indexOf(',') + 1);
    latitude = convert(str.substring(0, str.indexOf(',')), str.charAt(str.indexOf(',') + 1) == 'S');
    int val = latitude * 1000000;
    String s = String(val);
    lat_format = s.substring(0, (abs(latitude) < 100) ? 2 : 3);
    lat_format += '.';
    lat_format += s.substring((abs(latitude) < 100) ? 2 : 3);
    str = str.substring(str.indexOf(',') + 3);
    longitude = convert(str.substring(0, str.indexOf(',')), str.charAt(str.indexOf(',') + 1) == 'W');
    val = longitude * 1000000;
    s = String(val);
    lon_format = s.substring(0, (abs(longitude) < 100) ? 2 : 3);
    lon_format += '.';
    lon_format += s.substring((abs(longitude) < 100) ? 2 : 3);

    str = str.substring(str.indexOf(',') + 3);
    fix = str.charAt(0) - 48;
    str = str.substring(2);
    sat_num = str.substring(0, 2).toInt();
    str = str.substring(3);
    dop = str.substring(0, str.indexOf(',')).toFloat();
    str = str.substring(str.indexOf(',') + 1);
    altitude = str.substring(0, str.indexOf(',')).toFloat();
    str = str.substring(str.indexOf(',') + 3);
    geoid = str.substring(0, str.indexOf(',')).toFloat();

    if (isDebug()) {

      Serial.println("Done");
    }

    if (info->GPRMC[0] == '$') {

      if (isDebug()) {

        Serial.print("Parsing RMC data...");
      }

      str = (char*)(info->GPRMC);
      int comma = 0;

      for (int i = 0; i < 60; ++i) {

        if (info->GPRMC[i] == ',') {

          comma++;

          if (comma == 7) {

            comma = i + 1;
            break;
          }
        }
      }

      str = str.substring(comma);
      k_speed = str.substring(0, str.indexOf(',')).toFloat();
      m_speed = k_speed * 0.514;
      velocity = k_speed * 0.514;
      str = str.substring(str.indexOf(',') + 1);
      track_angle = str.substring(0, str.indexOf(',')).toFloat();
      str = str.substring(str.indexOf(',') + 1);
      day = str.substring(0, 2).toInt();
      month = str.substring(2, 4).toInt();
      year = str.substring(4, 6).toInt();
      date_format = "20";
      date_format += year;
      date_format += "-";
      date_format += month;
      date_format += "-";
      date_format += day;

      if (isDebug()) {

        Serial.println("Done");
      }

      return sat_num;
    }
  } else {

    if (isDebug()) {

      Serial.println("No GGA data");
    }
  }

  return 0;
}

// Public functions

void activateGPS() {
  LGPS.powerOn();

  if (isDebug()) {

    Serial.println("GPS started");
  }
}

bool activateGPSData() {

  if (getData(&info) > 3) {

    String str = "";
    str += date_format;
    str += ",";
    str += time_format;
    str += ",";
    str += lat_format;
    str += ",";
    str += lon_format;
    str += ",";
    str += altitude;
    str += ",";
    str += dop;
    str += ",";
    str += geoid;
    str += ",";
    str += track_angle;
    str += ",";
    str += m_speed;
    str += ",";
    str += k_speed;
    str += ",";
    str += fix;
    str += ",";
    str += sat_num;

    if (isDebug()) {

      Serial.println(str);
    }

    return true;
  } else {

    if (isDebug()) {

      Serial.println("Less then 4 satelites");
    }

    return false;
  }
}

String getLatitude() {

  if (latitude = 0.00000) {

    return old_lat_format;
  } else {

    old_lat_format = lat_format;

    return lat_format;
  }
}

String getLongitude() {

  if (longitude = 0.00000) {

    return old_lon_format;
  } else {

    old_lon_format = lat_format;

    return lon_format;
  }
}

String getDateTime() {
  String str = "";
  str += date_format;
  str += ",";
  str += time_format;

  if (latitude = 0.00000) {

    return old_time_and_date_format;
  } else {

    old_time_and_date_format = str;

    return str;
  }
}

float getVelocity() {

  return m_speed;
}
