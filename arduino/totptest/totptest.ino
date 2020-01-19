#include <RTClib.h>
#include <Wire.h>
#include <TOTP.h>
#include <rgb_lcd.h>

// The shared secret is ML9pIK9ImW
uint8_t hmacKey[] = {0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x77, 0x6f, 0x72, 0x6c, 0x64};
TOTP totp = TOTP(hmacKey, 10);
RTC_DS1307 RTC;
rgb_lcd lcd;

const int colorR = 0;
const int colorG = 0;
const int colorB = 255;

void setup()
{

  // Configure LCD
  lcd.begin(16,2);  
  lcd.setRGB(colorR, colorG, colorB);

  // Begin serial
  Serial.begin(9600);

  // Begin RTC
  Wire.begin();
  RTC.begin();

  // if (!RTC.isrunning()) {
  //   Serial.println("RTC is NOT running.");
  // }

//  DateTime now = RTC.now();
  // DateTime system = DateTime(__DATE__, __TIME__);

  // if (now.unixtime() < system.unixtime()) {
  //   Serial.println("Updating RTC clock with latest time...");
  RTC.adjust(DateTime(2020, 1, 18, 21, 33, 20));
  // }
}

void loop()
{
  DateTime now = RTC.now();

  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  lcd.print(" ");

  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);

  lcd.setCursor(0,1);

  char *newCode = totp.getCode(now.unixtime());
  lcd.print("PIN:");
  lcd.print(newCode);

   delay(1000);
  
  lcd.clear();

}
