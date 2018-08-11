/*
   User class
   Model and all functions for user
*/

class User {
  private:

  public:

    // User
    String userPhone = "";
    String userId = "";
    String userToken = "";

    // APN
    String apnName = "";
    String apnUser = "";
    String apnPassword = "";

    // Device
    String deviceName = "";

    // Files card
    String tokenFile = "token.txt";
    String userIdFile = "userId.txt";
    String userPhoneFile = "userPhone.txt";
    String apnNameFile = "apnName.txt";
    String apnUserFile = "apnUser.txt";
    String apnPasswordFile = "apnPass.txt";
    String deviceNameFile = "deviceName.txt";
    String serviceStatusFile = "service.txt";

    // Values
    String kServiceStatusActivated = "activated";
    String kServiceStatusDesactivated = "desactivated";

    // Functions
    // Set user token
    void setUserToken(String &string);

    // Set user id
    void setUserId(String &string);

    // Set user phone
    void setUserPhone(String &string);

    // Set apn name
    void setAPNName(String &string);

    // Set apn user
    void setAPNUser(String &string);

    // Set apn password
    void setAPNPassword(String &string);

    // Set device name
    void setDeviceNameForBluetooth(String &string);

    // Get user token
    String getUserToken();

    // Get user id
    String getUserId();

    // Get user phone
    String getUserPhone();

    // Get apn name
    String getAPNName();

    // Get apn user
    String getAPNUser();

    // Get apn password
    String getAPNPassword();

    // Get device name
    String getDeviceNameForBluetooth();

    // Get service status from SD Card
    bool getServiceStatusFromPersist();
};
