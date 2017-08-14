#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
SoftwareSerial mySerial(2, 3); // RX, TX

typedef struct SENSOR_DATA {

  uint8_t HEART_RATE;
  uint8_t SPO2;
  uint8_t SOUND;

} SENSOR_DATA;

uint8_t value = 0;

int INTERVAL = 1; //interval of measurements in minutes
int id = 0;

float Humi = 0.0F;
float Temp = 0.0F;

SENSOR_DATA sensor_data;

void setup() {

  
  Serial.begin(9600);
  Serial.println("Sleep Monitering System");
  mySerial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); //Start at character 4 on line 0
  lcd.print("SleepMonitering");
  delay(1000);
  lcd.clear();

  initializeSD();

  //set_time(0,21,10,6,11,8,17);
}

void loop() {

  id++;

  String entry = String(id);
  String dateEntry;

  sensor_data = get_random(&sensor_data);

  String s_Heart_Rate = String(sensor_data.HEART_RATE);
  String s_SPO2 = String(sensor_data.SPO2);
  String s_SOUND = String(sensor_data.SOUND);
  
  String s_Temp = String(read_temp(Temp));
  String s_Humi = String(read_humi(Humi));

  displayTime_LCD(); // display the real-time clock data on the Serial Monitor,

  dateEntry = DateLogEntry();
  entry = entry + "," + dateEntry + "," + s_Heart_Rate + "," + s_SPO2 + "," +  s_SOUND + "," + s_Temp + "," + s_Humi;
  writeEntryToFile(entry);
  
  delay(2000);
  sleepForMinutes(INTERVAL);

}
