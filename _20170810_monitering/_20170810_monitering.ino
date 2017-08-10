#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

uint16_t manufID, prodID;
uint8_t value = 0;

void setup() {

  lcd.begin();
  Serial.begin(9600);
  Serial.println("lcd Test");
  lcd.backlight();

  lcd.setCursor(0, 0); //Start at character 4 on line 0
  lcd.print("SleepMonitering");
  delay(1000);
  lcd.clear();

  getDeviceID(&manufID, &prodID);
  Serial.println(manufID, HEX);
  Serial.println(prodID, HEX);
  FRAM_Write_Byte(0, 40);
  //set_time(0,3,14,5,10,8,17);
}

void loop() {

  if (Serial.available()) {  //시리얼 모니터를 통해 들어오는 데이터가 있다면
    char data = Serial.read(); // 데이터를 data 변수에 저장

    // baklight 테스트
    if (data == '1') {
      lcd.noBacklight();
      delay(1000);
      lcd.backlight();
    }

    // Display 테스트 (글자 표시)
    if (data == '2') {
      lcd.noDisplay();
      delay(1000);
      lcd.display();
    }

    // Cursor Blink 테스트
    if (data == '3') {
      lcd.blink();
      delay(1000);
      lcd.noBlink();
    }

    // Cursor 표시 테스트
    if (data == '4') {
      lcd.cursor();
      delay(1000);
      lcd.noCursor();
    }

    // Scroll 테스트
    if (data  == '5') {
      lcd.scrollDisplayRight();
      delay(1000);
      lcd.scrollDisplayLeft();
    }

    // Cursor 위치 변경 테스트
    if (data  == '6') {
      lcd.home();
      lcd.cursor();
      for (int i = 0; i < 16; i++) {
        lcd.setCursor(i, 0);
        delay(100);
      }
      lcd.noCursor();
      lcd.home();
    }
  }
  displayTime_LCD(); // display the real-time clock data on the Serial Monitor,
  delay(1000); // every second

  value = FRAM_Read_Byte(0);
  Serial.println(value);

}




