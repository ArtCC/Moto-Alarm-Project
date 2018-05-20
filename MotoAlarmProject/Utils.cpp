// Import classes and libraries
#include "ImportClasses.h"

// Public functions
bool stringIsEmpty(String &string) {
  int lengthString = string.length();

  if (lengthString > 0) {

    return true;
  }

  return false;
}

bool checkIfStringContainOtherString(String &string, String &search) {

  if (string.substring(0, 6) == search) {

    return true;
  }

  return false;
}
