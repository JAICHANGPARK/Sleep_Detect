#define TEMP_REG 0xE3
#define HUMI_REG 0xE5

uint16_t readSHT20(uint8_t address){

  uint16_t result;
  Wire.beginTransmission(0x40);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.requestFrom(0x40,3);
  result = Wire.read() << 8;
  result += Wire.read();
  result &= ~0x0003;
  
  return result;
}

float read_temp(float temp){
  temp = ((-46.85) + (175.72/65536.6) * (float)readSHT20(TEMP_REG));
  return temp;
}

float read_humi(float humi){
   humi = ((-6.0) + (125.0/65536.6) * (float)readSHT20(HUMI_REG));
   return humi;
}









