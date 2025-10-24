#include "utils/helpers.hpp"
#include <WString.h>
#include <cstdio>

String Helpers::toHex(int r, int g, int b) {
  char hex[7];
  sprintf(hex, "%02X%02X%02X", r, g, b);
  return String(hex);
}
