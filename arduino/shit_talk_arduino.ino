#include "swRTC.h"
#include "TOTP.h"
#include "RTClib.h"
#include "rgb_lcd.h"

// The shared secret is MyLegoDoor
swRTC rtc;
uint8_t hmacKey[] = {0x4d, 0x79, 0x4c, 0x65, 0x67, 0x6f, 0x44, 0x6f, 0x6f, 0x72};
TOTP totp = TOTP(hmacKey, 10, 5);
char code[7];
rgb_lcd lcd;

const int colorR = 0;
const int colorG = 5;
const int colorB = 0;

void setup() {

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  Serial.begin(9600);
  rtc.stopRTC();
  // Adjust the following values to match the current date and time
  // and power on Arduino at the time set (use GMT timezone!)
  rtc.setDate(18, 1, 2020);
  rtc.setTime(9, 4, 00);
  rtc.startRTC();
}

void loop() {
  long GMT = rtc.getTimestamp();
  char* newCode = totp.getCode(GMT);
  if(strcmp(code, newCode) != 0) {
    lcd.clear();
    strcpy(code, newCode);
    Serial.println(code);
    Serial.println(GMT);
    lcd.print(code);
  }
}
