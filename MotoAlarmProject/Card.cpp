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

      Serial.print("File exist: ");
      Serial.println(fileNameString);
    }

    return true;
  }

  if (debug) {

    Serial.print("File not exist: ");
    Serial.println(fileNameString);
  }

  return false;
}

bool deleteFileFromSDCard(String &fileNameString) {
  char fileNameInArrayChar[15];
  fileNameString.toCharArray(fileNameInArrayChar, 15);
  char *fileName = fileNameInArrayChar;

  if (LSD.remove(fileName)) {

    if (debug) {

      Serial.print("File delete ok: ");
      Serial.println(fileNameString);
    }

    return true;
  }

  if (debug) {

    Serial.print("File not delete: ");
    Serial.println(fileNameString);
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

    Serial.print("Error opening: ");
    Serial.println(fileNameString);
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

      Serial.print("Error opening: ");
      Serial.println(fileNameString);
    }
  }

  if (debug) {

    Serial.print("getDataFromFile:String: ");
    Serial.println(dataString);
  }

  return dataString;
}
