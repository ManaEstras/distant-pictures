#include <SoftwareSerial.h>

#include <Adafruit_SSD1306.h>

#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>

#include <RTClib.h>
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;



#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
// Set this to true when you want to remap backticks to ESC (for testing the
// send text functionality).
bool test_sending_messages = true;

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(19200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Initiallizing...");
  display.display();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

}
}

int state = 0;
void loop() {
  // put your main code here, to run repeatedly:
  attachInterrupt(digitalPinToInterrupt(2), timing_ISR, RISING);
  delay(1000);
  displayTime();
  if(state) timing();

}

void displayTime(){
  DateTime now = rtc.now();
  Serial.println("RTC Clock");
  display.clearDisplay();
  display.setCursor(0,25);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.setCursor(0,0);
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.display();
}

void timing(){
  int i = 10;
  delay(1000);
  while(i > 0){
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.print(i);
    display.display();
    delay(1000);
    i--;
  }
  state = 0;
}

void timing_ISR(){
  if(state == 0) state = 1;
    
  }


