#include <qrcode.h>
#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <RTClib.h>
#include <TOTP.h>

// The shared secret is MyLegoDoor
uint8_t hmacKey[] = {0x4d, 0x4c, 0x39, 0x70, 0x49, 0x4b, 0x39, 0x49, 0x6d, 0x57};
TOTP totp = TOTP(hmacKey, 10);
char code[7];
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

  //Initialise LCD
  SeeedGrayOled.init(SH1107G);
}

void loop() {
  
  String url = "example.com/";
  url += random(1, 65535);

  Serial.print(url);

  char urlArr[sizeof(url)];
  url.toCharArray(urlArr, sizeof(urlArr));

  QRCode qrcode;  
  uint8_t qrcodeData[qrcode_getBufferSize(3)];;
  qrcode_initText(&qrcode, qrcodeData, 3, ECC_LOW, urlArr);
  
  unsigned char image[16384];
  int i = 0;

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        image[i] = 0xFF;
        image[i+1] = 0xFF;
        image[i+2] = 0xFF;
        image[i+3] = 0xFF;
      } else {
        image[i] = 0x00;
        image[i+1] = 0x00;
        image[i+2] = 0x00;
        image[i+3] = 0x00;

        Serial.print(" ");
      }
      i += 4;
    }
    Serial.println();
  }

  SeeedGrayOled.clearDisplay();
  SeeedGrayOled.drawBitmap(image, sizeof image);

  delay(5000);

}
