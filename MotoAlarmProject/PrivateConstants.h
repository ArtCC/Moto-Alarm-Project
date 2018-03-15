/*
   PrivateConstants class
   All private constants in class
   NOT DELETED ANY CONSTANT
*/

// First init
static bool firstInit = true;

// Instance for all request
static LGPRSClient client;

// Max response time from server
const unsigned long HTTP_TIMEOUT = 10000;

// Server
static char server[] = "motoalarm-project.com";
static char folderForUpdate[] = "update";
static char portForUpdate[] = "80";
static int port = 80;

// Token
static String headToken = "Bearer ";
static String userToken = "";

// Bluetooth
static char* activateText = "on";
static char* desactivateText = "off";

// Alarm
static bool alarmSMSActive = false;

// Show logs, set true
static bool debug = false;
