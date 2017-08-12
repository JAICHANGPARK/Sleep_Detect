#include <EEPROM.h>

void EEPROM_Clear() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
    Serial.println(i);
  }
}
