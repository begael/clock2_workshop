#include <Superbe_rtc_DS1302.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

const int rtc_CLK = A5;
const int rtc_DATA = A4;
const int rtc_CE = A3;
const int boutonHeure = 10;
const int boutonMinute = 11;
const int boutonCouleur = 12;
const int ledsPin = 8;
const int nombreLeds = 110;
const int intervalleTemps = 1000;
const int eepromAddress = 1;
const int nColorMax = 12;
int nColor;
int myHeure;
int myMinute;
boolean boutonPushed = false;
unsigned long chrono;
Rtc_DS1302 rtc;
int lumR[nColorMax] = {0, 255, 128, 64, 32, 255, 192, 128, 0, 0, 0, 128};
int lumG[nColorMax] = {0, 255, 128, 64, 32, 0, 96, 128, 255, 128, 0, 0};
int lumB[nColorMax] = {0, 255, 128, 64, 32, 0, 0, 0, 0, 128, 255, 128};
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(nombreLeds, ledsPin);

void setup() {
  pinMode(boutonHeure, INPUT_PULLUP);
  pinMode(boutonMinute, INPUT_PULLUP);
  pinMode(boutonCouleur, INPUT_PULLUP);
  rtc.begin(rtc_CLK, rtc_DATA, rtc_CE);
  pixels.begin();
  pixels.setPixelColor(0, 0, 0, 0);
  pixels.show();
  nColor = EEPROM.read(eepromAddress);
  lumR[0] = EEPROM.read(eepromAddress+1);
  lumG[0] = EEPROM.read(eepromAddress+2);
  lumB[0] = EEPROM.read(eepromAddress+3);
  Serial.begin(9600);
  Serial.println("bonjour. la liste des couleurs est :");
  for (int i = 0; i < nColorMax; i++) {
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(lumR[i]);
    Serial.print(" ");
    Serial.print(lumG[i]);
    Serial.print(" ");
    Serial.println(lumB[i]);
  }
  Serial.print("actuellement, le choix est : ");
  Serial.println(nColor);
  Serial.println("il est : (tapez quelque chose pour editer)");
}

void loop() {
  if (Serial.available() > 0) {
      modifierHeure();
  }
  if (!digitalRead(boutonHeure) || !digitalRead(boutonMinute) || !digitalRead(boutonCouleur)) {
    boutonPushed = true;
    chrono = millis();
    if (!digitalRead(boutonHeure)) {
      myHeure ++;
      if (myHeure >= 24) myHeure = 0;
    }
    if (!digitalRead(boutonMinute)) {
      myMinute += 5;
      myMinute = myMinute - myMinute%5;
      if (myMinute >= 60) myMinute = 0;
    }
    if (!digitalRead(boutonCouleur)) {
      nColor++;
      if (nColor >= nColorMax) nColor = 0;
    }
  }
  if (boutonPushed) {
    if (millis() - chrono > 10000ul) {
      boutonPushed = false;
      rtc.writeTime(myHeure, myMinute, 0);
      EEPROM.write(eepromAddress, nColor);
    }
  } else {
    rtc.readDateTime();
    myHeure = rtc.hour;
    myMinute = rtc.minute;
  }
  Serial.print(myHeure);
  Serial.print(":");
  Serial.print(myMinute);
  Serial.print(":");
  Serial.println(rtc.second);
  int heureDisplay = myHeure;
  if (myMinute > 34) {
    heureDisplay++;
  }
  for (int i = 0; i < nombreLeds; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.setPixelColor(109, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
  pixels.setPixelColor(108, lumR[nColor], lumG[nColor], lumB[nColor]);  // L
  pixels.setPixelColor(106, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
  pixels.setPixelColor(105, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  pixels.setPixelColor(104, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
  if (heureDisplay == 0 || heureDisplay == 24) {
    pixels.setPixelColor(60, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(59, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(58, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(57, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(56, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(55, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
  } else if (heureDisplay == 1 || heureDisplay == 13) {
    pixels.setPixelColor(83, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(82, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(81, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
  } else if (heureDisplay == 2 || heureDisplay == 14) {
    pixels.setPixelColor(102, lumR[nColor], lumG[nColor], lumB[nColor]);  // D
    pixels.setPixelColor(101, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(100, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(99, lumR[nColor], lumG[nColor], lumB[nColor]);  // X
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 3 || heureDisplay == 15) {
    pixels.setPixelColor(98, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
    pixels.setPixelColor(97, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(96, lumR[nColor], lumG[nColor], lumB[nColor]);  // O
    pixels.setPixelColor(95, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(94, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 4 || heureDisplay == 16) {
    pixels.setPixelColor(93, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
    pixels.setPixelColor(92, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(91, lumR[nColor], lumG[nColor], lumB[nColor]);  // A
    pixels.setPixelColor(90, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
    pixels.setPixelColor(89, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(88, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 5 || heureDisplay == 17) {
    pixels.setPixelColor(76, lumR[nColor], lumG[nColor], lumB[nColor]);  // C
    pixels.setPixelColor(75, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(74, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(73, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 6 || heureDisplay == 18) {
    pixels.setPixelColor(72, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(71, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(70, lumR[nColor], lumG[nColor], lumB[nColor]);  // X
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 7 || heureDisplay == 19) {
    pixels.setPixelColor(80, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(79, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(78, lumR[nColor], lumG[nColor], lumB[nColor]);  // P
    pixels.setPixelColor(77, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 8 || heureDisplay == 20) {
    pixels.setPixelColor(69, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(68, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(67, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(66, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 9 || heureDisplay == 21) {
    pixels.setPixelColor(87, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(86, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(85, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(84, lumR[nColor], lumG[nColor], lumB[nColor]);  // F
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 10 || heureDisplay == 22) {
    pixels.setPixelColor(63, lumR[nColor], lumG[nColor], lumB[nColor]);  // D
    pixels.setPixelColor(62, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(61, lumR[nColor], lumG[nColor], lumB[nColor]);  // X
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 11 || heureDisplay == 23) {
    pixels.setPixelColor(47, lumR[nColor], lumG[nColor], lumB[nColor]);  // O
    pixels.setPixelColor(46, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(45, lumR[nColor], lumG[nColor], lumB[nColor]);  // Z
    pixels.setPixelColor(44, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(54, lumR[nColor], lumG[nColor], lumB[nColor]);  // H
    pixels.setPixelColor(53, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(52, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(51, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(50, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(49, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
  } else if (heureDisplay == 12) {
    pixels.setPixelColor(65, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(64, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(63, lumR[nColor], lumG[nColor], lumB[nColor]);  // D
    pixels.setPixelColor(62, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
  }
  if (myMinute < 5) {
  } else if (myMinute < 10) {
    pixels.setPixelColor(15, lumR[nColor], lumG[nColor], lumB[nColor]);  // C
    pixels.setPixelColor(14, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(13, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(12, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
  } else if (myMinute < 15) {
    pixels.setPixelColor(35, lumR[nColor], lumG[nColor], lumB[nColor]);  // D
    pixels.setPixelColor(34, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(33, lumR[nColor], lumG[nColor], lumB[nColor]);  // X
  } else if (myMinute < 20) {
    pixels.setPixelColor(29, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
    pixels.setPixelColor(28, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(27, lumR[nColor], lumG[nColor], lumB[nColor]);  // A
    pixels.setPixelColor(26, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(25, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
  } else if (myMinute < 25) {
    pixels.setPixelColor(21, lumR[nColor], lumG[nColor], lumB[nColor]);  // V
    pixels.setPixelColor(20, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(19, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(18, lumR[nColor], lumG[nColor], lumB[nColor]);  // G
    pixels.setPixelColor(17, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
  } else if (myMinute < 30) {
    pixels.setPixelColor(21, lumR[nColor], lumG[nColor], lumB[nColor]);  // V
    pixels.setPixelColor(20, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(19, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(18, lumR[nColor], lumG[nColor], lumB[nColor]);  // G
    pixels.setPixelColor(17, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
    pixels.setPixelColor(16, lumR[nColor], lumG[nColor], lumB[nColor]);  // -
    pixels.setPixelColor(15, lumR[nColor], lumG[nColor], lumB[nColor]);  // C
    pixels.setPixelColor(14, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(13, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(12, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
  } else if (myMinute < 35) {
    pixels.setPixelColor(0, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(1, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
    pixels.setPixelColor(6, lumR[nColor], lumG[nColor], lumB[nColor]);  // D
    pixels.setPixelColor(5, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    pixels.setPixelColor(4, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(3, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    if (heureDisplay != 0 && heureDisplay != 12) {
      pixels.setPixelColor(7, lumR[nColor], lumG[nColor], lumB[nColor]);  // E
    }
  } else if (myMinute < 40) {
    pixels.setPixelColor(43, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(42, lumR[nColor], lumG[nColor], lumB[nColor]);  // O
    pixels.setPixelColor(41, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(40, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(39, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(21, lumR[nColor], lumG[nColor], lumB[nColor]);  // V
    pixels.setPixelColor(20, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(19, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(18, lumR[nColor], lumG[nColor], lumB[nColor]);  // G
    pixels.setPixelColor(17, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
    pixels.setPixelColor(16, lumR[nColor], lumG[nColor], lumB[nColor]);  // -
    pixels.setPixelColor(15, lumR[nColor], lumG[nColor], lumB[nColor]);  // C
    pixels.setPixelColor(14, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(13, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(12, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
  } else if (myMinute < 45) {
    pixels.setPixelColor(43, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(42, lumR[nColor], lumG[nColor], lumB[nColor]);  // O
    pixels.setPixelColor(41, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(40, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(39, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(21, lumR[nColor], lumG[nColor], lumB[nColor]);  // V
    pixels.setPixelColor(20, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(19, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(18, lumR[nColor], lumG[nColor], lumB[nColor]);  // G
    pixels.setPixelColor(17, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
  } else if (myMinute < 50) {
    pixels.setPixelColor(43, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(42, lumR[nColor], lumG[nColor], lumB[nColor]);  // O
    pixels.setPixelColor(41, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(40, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(39, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(29, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
    pixels.setPixelColor(28, lumR[nColor], lumG[nColor], lumB[nColor]);  // U
    pixels.setPixelColor(27, lumR[nColor], lumG[nColor], lumB[nColor]);  // A
    pixels.setPixelColor(26, lumR[nColor], lumG[nColor], lumB[nColor]);  // R
    pixels.setPixelColor(25, lumR[nColor], lumG[nColor], lumB[nColor]);  // T
  } else if (myMinute < 55) {
    pixels.setPixelColor(43, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(42, lumR[nColor], lumG[nColor], lumB[nColor]);  // O
    pixels.setPixelColor(41, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(40, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(39, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(35, lumR[nColor], lumG[nColor], lumB[nColor]);  // D
    pixels.setPixelColor(34, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(33, lumR[nColor], lumG[nColor], lumB[nColor]);  // X
  } else {
    pixels.setPixelColor(43, lumR[nColor], lumG[nColor], lumB[nColor]);  // M
    pixels.setPixelColor(42, lumR[nColor], lumG[nColor], lumB[nColor]);  // O
    pixels.setPixelColor(41, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(40, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(39, lumR[nColor], lumG[nColor], lumB[nColor]);  // S
    pixels.setPixelColor(15, lumR[nColor], lumG[nColor], lumB[nColor]);  // C
    pixels.setPixelColor(14, lumR[nColor], lumG[nColor], lumB[nColor]);  // I
    pixels.setPixelColor(13, lumR[nColor], lumG[nColor], lumB[nColor]);  // N
    pixels.setPixelColor(12, lumR[nColor], lumG[nColor], lumB[nColor]);  // Q
  }
  if (boutonPushed) {
    pixels.setPixelColor(109, 255, 0, 0);  // I
    pixels.setPixelColor(108, 255, 0, 0);  // L
  }
  pixels.show();
  delay(intervalleTemps);
}

void modifierHeure() {
  Serial.println("heure :");
  while(Serial.available() > 0) Serial.read();
  while(Serial.available() == 0) delay(10);
  myHeure = Serial.parseInt();
  Serial.println("minute :");
  while(Serial.available() > 0) Serial.read();
  while(Serial.available() == 0) delay(10);
  myMinute = Serial.parseInt();
  Serial.println("luminosite perso rouge (0-255) :");
  while(Serial.available() > 0) Serial.read();
  while(Serial.available() == 0) delay(10);
  lumR[0] = Serial.parseInt();
  Serial.println("luminosite perso verte (0-255) :");
  while(Serial.available() > 0) Serial.read();
  while(Serial.available() == 0) delay(10);
  lumG[0] = Serial.parseInt();
  Serial.println("luminosite perso bleue (0-255) :");
  while(Serial.available() > 0) Serial.read();
  while(Serial.available() == 0) delay(10);
  lumB[0] = Serial.parseInt();
  Serial.print("choix couleur (0-");
  Serial.print(nColorMax);
  Serial.println(") :");
  while(Serial.available() > 0) Serial.read();
  while(Serial.available() == 0) delay(10);
  nColor = Serial.parseInt();
  rtc.writeTime(myHeure, myMinute, 0);
  EEPROM.write(eepromAddress, nColor);
  EEPROM.write(eepromAddress+1, lumR[0]);
  EEPROM.write(eepromAddress+2, lumG[0]);
  EEPROM.write(eepromAddress+3, lumB[0]);
  while(Serial.available() > 0) Serial.read();
}
