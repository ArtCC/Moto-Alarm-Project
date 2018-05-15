/*
   PublicConstants class
   All public constants in class
*/

// Device name
#define DEVICE_NAME "MotoAlarmProject"

// APN config
#define APN_NAME "apnName"
#define APN_USER ""
#define APN_PASSWORD ""

// WiFi config
#define WIFI_AP "SSID"
#define WIFI_PASSWORD "WIFI_PASSWORD"

// WiFi active or not
static bool wifiIsActive = false;

// User
static char* userPhone = "+34600000000";
static String userMail = "\"mail@mail.com\"";
static String userPassword = "\"userPassword\"";
static String userId = "userId";

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
