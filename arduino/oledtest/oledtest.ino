#include <U8g2lib.h>
#include <qrcode.h>
#include <Wire.h>
#include <RTClib.h>
#include <TOTP.h>

// The shared secret is MyLegoDoor
uint8_t hmacKey[] = {0x4d, 0x4c, 0x39, 0x70, 0x49, 0x4b, 0x39, 0x49, 0x6d, 0x57};
TOTP totp = TOTP(hmacKey, 10);
RTC_DS1307 RTC;
U8G2_SH1107_SEEED_128X128_2_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {

  // Begin serial
  Serial.begin(9600);
  
  // Begin RTC & calibrate if need be
  Wire.begin();
  RTC.begin();

  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running.");
  }

  //Initialise LCD
  u8g2.begin();
  u8g2.setDrawColor(1);
}

void loop() {

  QRCode qrcode;  
  uint8_t qrcodeData[qrcode_getBufferSize(1)];;
  qrcode_initText(&qrcode, qrcodeData, 1, ECC_LOW, "H");

  Serial.println("QR Generated");
  
  u8g2.clearDisplay();

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        u8g2.drawBox(x, y, 1, 1);
      }
    }
    u8g2.sendBuffer();
    u8g2.clearBuffer();
  }

  u8g2.clearBuffer();
  Serial.println("Displayed.");
  
  delay(15000);

}
