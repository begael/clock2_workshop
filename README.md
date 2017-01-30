# clock2_workshop

Arduino software for a Clock2 workshop.

You need the Adafruit_Neopixel Library.
And you find the RTC library in my repositories.

If you have a DS1307, you have to change :
- all 1302 => 1307
- include Wire Library
- rtc.begin(int, int, int) => rtc.begin()
