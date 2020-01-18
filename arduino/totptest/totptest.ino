#include <RTClib.h>
#include <Wire.h>
#include <TOTP.h>

// The shared secret is ML9pIK9ImW
uint8_t hmacKey[] = {0x4d, 0x4c, 0x39, 0x70, 0x49, 0x4b, 0x39, 0x49, 0x6d, 0x57};
TOTP totp = TOTP(hmacKey, 10);
RTC_DS1307 RTC;

void setup() {

  // Begin serial
  Serial.begin(9600);
  
  // Begin RTC & calibrate if need be
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
  
  Serial.print("Current time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
  char* newCode = totp.getCode(now.unixtime());
  Serial.println(newCode);

  delay(5000);

}
