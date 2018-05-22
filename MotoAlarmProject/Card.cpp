// Import classes and libraries
#include "ImportClasses.h"

// Public functions
void configSDCard() {

  if (debug) {

    Serial.println("Initializing SD card...");
  }

  LSD.begin();

  if (debug) {

    Serial.println("Card initialized!");
  }
}

bool checkIFFileExistInSDCard(String &fileNameString) {
  char fileNameInArrayChar[15];
  fileNameString.toCharArray(fileNameInArrayChar, 15);
  char *fileName = fileNameInArrayChar;

  if (LSD.exists(fileName)) {

    if (debug) {

      Serial.println("File exist");
    }

    return true;
  }

  if (debug) {

    Serial.println("File not exist!");
  }

  return false;
}

bool deleteFileFromSDCard(String &fileNameString) {
  char fileNameInArrayChar[15];
  fileNameString.toCharArray(fileNameInArrayChar, 15);
  char *fileName = fileNameInArrayChar;

  if (LSD.remove(fileName)) {

    if (debug) {

      Serial.println("File delete ok");
    }

    return true;
  }

  if (debug) {

    Serial.println("File not delete!");
  }

  return false;
}

bool setDataInFile(String &fileNameString, String &dataString) {
  char fileNameInArrayChar[15];
  fileNameString.toCharArray(fileNameInArrayChar, 15);
  char *fileName = fileNameInArrayChar;

  LFile dataFile = LSD.open(fileName, FILE_WRITE);

  // If the file is available, write to it
  if (dataFile) {

    dataFile.println(dataString);

    dataFile.close();

    return true;
  }

  if (debug) {

    Serial.println("Error opening: ");
    Serial.println("fileName");
  }

  return false;
}

String getDataFromFile(String &fileNameString) {
  String dataString = "";

  char fileNameInArrayChar[15];
  fileNameString.toCharArray(fileNameInArrayChar, 15);
  char *fileName = fileNameInArrayChar;

  LFile dataFile = LSD.open(fileName);

  // If the file is available, read from it
  if (dataFile) {

    char character;

    while (dataFile.available()) {

      character = dataFile.read();
      dataString.concat(character);
    }

    dataFile.close();
  } else {

    if (debug) {

      Serial.println("Error opening: ");
      Serial.println("fileName");
    }
  }

  if (debug) {

    Serial.println("getDataFromFile:String: ");
    Serial.println(dataString);
  }

  return dataString;
}
