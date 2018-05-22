/*
   PrivateConstants class
   All private constants in class
   NOT DELETED ANY CONSTANT
*/

// Properties
// "Multi-thread" with millis() for update MPU6050 status
static unsigned long intervalUpdateForMPU6050 = 1000;
static unsigned long previousMillisForMPU6050 = 0;

// Instance for all request
static LGPRSClient client;

// Max response time from server
const unsigned long HTTP_TIMEOUT = 10000;
const size_t MAX_CONTENT_SIZE = 512;

// Server
static char *mapServer = "motoalarm-project.com";
static int port = 80;

// Bluetooth
static String serviceOn = "on";
static String serviceOff = "off";
static bool serviceActive;

// Device update
static bool deviceUpdateEnabled = true;
#define mapServer_UPDATE "motoalarm-project.com"
#define MAP_FOLDER_UPDATE "update"
#define MAP_PORT_UPDATE "80"

// Text for SMS and request POST
static String textForStatusSMS = "My coordinates on map: ";
static String textForStatusErrorSMS = "Sorry, my coordinates on map contain errors...";
static String textForBatterySMS = "Right now, I have this battery percentage: ";
static String textForFeelSMS = "I'm fine. Thank you very much! :)";
static String textForResetSMS = "Wait, I'm restarting now...";
static String textForResetSMSDisabled = "Sorry, this functionality is not in use yet...";
static String textForActivateSMS = "Perfect! My location is active :)";
static String textForDesactivateSMS = "Oops... Now my location is disabled :(";
static String textForWetSMS = "I'm very wet... ";
static String textForColdSMS = "I'm very cold... ";
static String textForHotSMS = "I'm very hot... ";
static String textForAlarmSMS = "Hey! I'm moving! Speed: ";
static String textForAlarmSMSWithoutLocation = "Hey! I'm moving!";

// Show logs, set true
static bool debug = false;
