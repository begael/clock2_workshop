#include <Superbe_rtc_DS1302.h>
#include <Adafruit_NeoPixel.h>

const int rtc_CLK = A5;
const int rtc_DATA = A4;
const int rtc_CE = A3;
const int boutonHeure = 10;
const int boutonMinute = 11;
const int boutonCouleur = 12;
const int ledsPin = 8;
const int nombreLeds = 110;
const int intervalleTemps = 1000;
Rtc_DS1302 rtc;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(nombreLeds, ledsPin);

void setup() {
  pinMode(boutonHeure, INPUT_PULLUP);
  pinMode(boutonMinute, INPUT_PULLUP);
  pinMode(boutonCouleur, INPUT_PULLUP);
  rtc.begin(rtc_CLK, rtc_DATA, rtc_CE);
  pixels.begin();
  pixels.setPixelColor(0, 0, 0, 0);
  pixels.show();
  Serial.begin(9600);
  Serial.println("bonjour.");
  rtc.writeDateTime(17, 2, 1, 3, 18, 56, 00);  //!!! pas 2015 !!! pour mettre à l'heure
}

void loop() {
  rtc.readDateTime();
  Serial.print(rtc.weekDay);
  Serial.print(",");
  Serial.print(rtc.monthDay);
  Serial.print("/");
  Serial.print(rtc.month);
  Serial.print("/");
  Serial.print(rtc.year);
  Serial.print(" ");
  Serial.print(rtc.hour);
  Serial.print(":");
  Serial.print(rtc.minute);
  Serial.print(":");
  Serial.println(rtc.second);
  int r = 0;
  int g = 0;
  int b = 0;
  if (!digitalRead(boutonHeure)) r = 255;
  if (!digitalRead(boutonMinute)) g = 255;
  if (!digitalRead(boutonCouleur)) b = 255;
  for (int i = 0; i < nombreLeds; i++) {
    pixels.setPixelColor(i, r, g, b);
  }
  pixels.show();
  delay(intervalleTemps);
}
