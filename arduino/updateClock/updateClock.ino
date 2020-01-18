#include <Wire.h>
#include <RTClib.h>
#include <rgb_lcd.h>

// The shared secret is MyLegoDoor
uint8_t hmacKey[] = {0x4d, 0x79, 0x4c, 0x65, 0x67, 0x6f, 0x44, 0x6f, 0x6f, 0x72};
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

  Serial.println("Updating RTC clock with latest time...");
  RTC.adjust(DateTime(2020, 1, 18, 16, now.minute(), now.second()));
}

void loop() {

  DateTime now = RTC.now();

  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year()%100, DEC);

  lcd.print(' ');

  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  delay(1000);
  
  lcd.clear();
}
