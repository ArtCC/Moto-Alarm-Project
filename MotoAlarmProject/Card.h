/*
   Card class
   All functions for save and get data from SD card
*/

class Card {
  private:

  public:

    // Config SD card
    void configSDCard();

    // Check file in SD Card
    bool checkIFFileExistInSDCard(String &fileNameString);

    // Delete file from SD card
    bool deleteFileFromSDCard(String &fileNameString);

    // Save data string in SD card
    bool setDataInFile(String &fileNameString, String &dataString);

    // get data string from SD card
    String getDataFromFile(String &fileNameString);
};
