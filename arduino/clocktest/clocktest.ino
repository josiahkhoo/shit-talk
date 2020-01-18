#include <Wire.h>
#include <RTClib.h>
#include <rgb_lcd.h>
#include <TOTP.h>

// The shared secret is MyLegoDoor
uint8_t hmacKey[] = {0x4d, 0x79, 0x4c, 0x65, 0x67, 0x6f, 0x44, 0x6f, 0x6f, 0x72};
TOTP totp = TOTP(hmacKey, 10, 5);
char code[7];
rgb_lcd lcd;
RTC_DS1307 RTC;

const int colorR = 0;
const int colorG = 0;
const int colorB = 255;

void setup() {

  // Configure LCD
  lcd.begin(16,2);  
  lcd.setRGB(colorR, colorG, colorB);

  // Begin serial
  Serial.begin(9600);

  // Begin RTC
  Wire.begin();
  RTC.begin();

  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running.");
  }

  DateTime now = RTC.now();
  DateTime system = DateTime(__DATE__, __TIME__);

  if (now.unixtime() < system.unixtime()) {
    Serial.println("Updating RTC clock with latest time...");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {

  DateTime now = RTC.now();

  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  
  lcd.setCursor(0,1);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  delay(1000);
  
  lcd.clear();
  
//  long GMT = rtc.getTimestamp();
//  char* newCode = totp.getCode(GMT);
//  if(strcmp(code, newCode) != 0) {
//    lcd.clear();
//    strcpy(code, newCode);
//    Serial.println(code);
//    Serial.println(GMT);
//    lcd.print(code);
//  }
}
