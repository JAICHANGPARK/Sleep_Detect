#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LowPower.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

uint16_t manufID, prodID;
uint8_t value = 0;

int INTERVAL = 1; //interval of measurements in minutes
int id = 0;

void setup() {

  lcd.begin();
  Serial.begin(9600);
  Serial.println("Sleep Monitering System");
  lcd.backlight();

  lcd.setCursor(0, 0); //Start at character 4 on line 0
  lcd.print("SleepMonitering");
  delay(1000);
  lcd.clear();

  //  getDeviceID(&manufID, &prodID);
  //  Serial.println(manufID, HEX);
  //  Serial.println(prodID, HEX);
  //set_time(0,42,19,5,10,8,17);
  
  initializeSD();
  
}

void loop() {

  id++;

  String entry;
  String dateEntry;

  displayTime_LCD(); // display the real-time clock data on the Serial Monitor,
  //delay(1000); // every second

  dateEntry = DateLogEntry();
  entry = String(id) + "," + dateEntry;
  writeEntryToFile(entry);
  delay(2000);
  sleepForMinutes(INTERVAL);
  
}
