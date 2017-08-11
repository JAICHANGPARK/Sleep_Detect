#define MB85RC_DEFAULT_ADDRESS    (0x50) /* 1010 + A2 + A1 + A0 = 0x50 default */
#define MB85RC_SLAVE_ID           (0xF8)

uint8_t i2c_addr = MB85RC_DEFAULT_ADDRESS;

/**************************************************************************/
/*!
    @brief  Reads the Manufacturer ID and the Product ID frm the IC

    @params[out]  manufacturerID
                  The 12-bit manufacturer ID (Fujitsu = 0x00A)
    @params[out]  productID
                  The memory density (bytes 11..8) and proprietary
                  Product ID fields (bytes 7..0). Should be 0x510 for
                  the MB85RC256V.
*/
/**************************************************************************/
void getDeviceID(uint16_t *manufacturerID, uint16_t *productID)
{
  uint8_t a[3] = { 0, 0, 0 };
  uint8_t results;

  Wire.beginTransmission(MB85RC_SLAVE_ID >> 1);
  Wire.write(i2c_addr << 1);
  results = Wire.endTransmission(false);

  Wire.requestFrom(MB85RC_SLAVE_ID >> 1, 3);
  a[0] = Wire.read();
  a[1] = Wire.read();
  a[2] = Wire.read();

  /* Shift values to separate manuf and prod IDs */
  /* See p.10 of http://www.fujitsu.com/downloads/MICRO/fsa/pdf/products/memory/fram/MB85RC256V-DS501-00017-3v0-E.pdf */
  *manufacturerID = (a[0] << 4) + (a[1]  >> 4);
  *productID = ((a[1] & 0x0F) << 8) + a[2];
}

void FRAM_Write_Byte (uint16_t framAddr, uint8_t value)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(framAddr >> 8);
  Wire.write(framAddr & 0xFF);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t FRAM_Read_Byte (uint16_t framAddr)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(framAddr >> 8);
  Wire.write(framAddr & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(i2c_addr, (uint8_t)1);

  return Wire.read();
}


