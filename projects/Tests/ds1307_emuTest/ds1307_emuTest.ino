// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
void setup () {
Serial.begin(9600);
Wire.begin();
RTC.begin();
if (! RTC.isrunning()) {
Serial.println("RTC is NOT running!");
// following line sets the RTC to the date & time this sketch was compiled

}

}
void loop () {
DateTime now = RTC.now();
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

while(!Serial.available());
Serial.read();
RTC.adjust(DateTime(__DATE__, __TIME__));
}
