#define DS1307_ADDRESS 0x68
/**
   Deciaml을 BCD로 변환하는 함수
   @param : val ( BCB 값)
*/
byte decToBcd(byte val) {
  // Convert normal decimal numbers to binary coded decimal
  return ( (val / 10 * 16) + (val % 10) );
}
/**
   BCD를 Decimal로 변환하는 함수
   @param : val ( BCB 값)
*/
byte bcdToDec(byte val) {
  // Convert binary coded decimal to normal decimal numbers
  return ( (val / 16 * 10) + (val % 16) );
}

/**
   DS1307모듈의 초기 시간을 설정하는 함수
   초기에 한번만 설정하면 된다.
   @param : 초 , 분, 시, 요일,일,월,년 순 입력
*/
void set_time(byte second, byte minute, byte hour,
              byte dayOfWeek, byte dayOfMonth, byte month, byte year) {

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

/**
   DS1307모듈에서 시간을 읽는 함수
   주소는 자동 증가 ( 데이터 시트 참고 )
   @param : 초 , 분, 시, 요일,일,월,년 순 입력
*/

void read_time(byte *second, byte *minute, byte *hour,
               byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime_Serial()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  read_time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  Serial.print(hour, DEC);
  Serial.print(":");
  if (minute < 10) {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second < 10) {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch (dayOfWeek) {
    case 1:
      Serial.println("Sunday");
      break;
    case 2:
      Serial.println("Monday");
      break;
    case 3:
      Serial.println("Tuesday");
      break;
    case 4:
      Serial.println("Wednesday");
      break;
    case 5:
      Serial.println("Thursday");
      break;
    case 6:
      Serial.println("Friday");
      break;
    case 7:
      Serial.println("Saturday");
      break;
  }
}

void displayTime_LCD()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  read_time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  lcd.setCursor(0, 0);
  lcd.print(hour);

  lcd.setCursor(2, 0);
  lcd.print(":");

  lcd.setCursor(3, 0);
  lcd.print(minute);

  lcd.setCursor(5, 0);
  lcd.print(":");

  lcd.setCursor(6, 0);
  lcd.print(second);

  lcd.setCursor(0, 1);
  lcd.print("20");
  lcd.setCursor(2, 1);
  lcd.print(year);
  lcd.setCursor(4, 1);
  lcd.print("-");

  lcd.setCursor(5, 1);
  lcd.print(month);
  lcd.setCursor(7, 1);
  lcd.print("-");

  lcd.setCursor(8, 1);
  lcd.print(dayOfMonth);

  lcd.setCursor(11, 0);

  switch (dayOfWeek) {
    case 1:
      lcd.print("SUN");
      break;
    case 2:
      lcd.print("MON");
      break;
    case 3:
      lcd.print("TUE");
      break;
    case 4:
      lcd.print("WED");
      break;
    case 5:
      lcd.print("THU");
      break;
    case 6:
      lcd.print("FRI");
      break;
    case 7:
      lcd.print("SAT");
      break;
  }
}

String DateLogEntry(){
  
  String s_dateEntry;
  String s_year;
  String s_month;
  String s_day;
  String s_hour;
  String s_minute;

  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  read_time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  s_year = String(year);
  s_month = String(month);
  s_day = String(dayOfMonth);

  if (hour < 10){
    s_hour = "0" + String(hour);
  } else{
    s_hour = String(hour);
  }

  if (minute < 10){
    s_minute = "0" + String(minute);
  } else{
    s_minute = String(minute);
  }

  s_dateEntry = s_month + "/" + s_day + "/" + s_year + " " + s_hour + ":" + s_minute;
  
  return s_dateEntry;
}


