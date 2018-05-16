/*
   PrivateConstants class
   All private constants in class
   NOT DELETED ANY CONSTANT
*/

// Properties
// First init
static bool firstInit = true;
static bool gpsOK = false;

// "Multi-thread" with millis() for update MPU6050 status
static unsigned long intervalUpdateForMPU6050 = 2500;
static unsigned long previousMillisForMPU6050 = 0;

// "Multi-thread" with millis() for check connection status
static unsigned long intervalUpdateForConnectionCheck = 60000;
static unsigned long previousMillisForConnectionCheck = 0;

// Instance for all request
static LGPRSClient client;

// Max response time from server
const unsigned long HTTP_TIMEOUT = 10000;
const size_t MAX_CONTENT_SIZE = 512;

// Server
#define MAP_SERVER "motoalarm-project.com"
static int port = 80;

// Token
static String headToken = "Bearer ";
static String userToken = "";

// Bluetooth
#define ACTIVATE_TEXT "on"
#define DESACTIVATE_TEXT "off"

// Wifi
static LWiFiClient clientWifi;
#define WIFI_AUTH LWIFI_WPA

// Test
#define PING_TO_SERVER "start.duckduckgo.com"

// Alarm
static bool alarmSMSActive = true;

// Show logs, set true
static bool debug = false;
