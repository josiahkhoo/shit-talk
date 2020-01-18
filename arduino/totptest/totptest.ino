#include <RTClib.h>
#include <Wire.h>
#include <TOTP.h>

// The shared secret is ML9pIK9ImW
uint8_t hmacKey[] = {0x4a, 0x56, 0x47, 0x44, 0x53, 0x34, 0x43, 0x4a, 0x4a, 0x4d, 0x34, 0x55, 0x53, 0x33, 0x4b, 0x58};
TOTP totp = TOTP(hmacKey, 16);
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
