/***************************************************
  This is an example sketch for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

DeviceAddress insideThermometer = { 0x28, 0xA7, 0xC8, 0x5A, 0x03, 0x00, 0x00, 0xFC };

//Use these pins for the shield!
#define sclk 13
#define mosi 11
#define cs   10
#define dc   8
#define rst  0  // you can also connect this to the Arduino reset



#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// Option 1: use any pins but a little slower
//Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

// Option 2: must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

float temp;
void setup(void) {
  tft.initR(INITR_BLACKTAB);  
  sensors.begin();
  sensors.setResolution(insideThermometer, 12);
}

void loop() {
  sensors.requestTemperatures();
  temp = sensors.getTempC(insideThermometer);
  delay(2000);
  
  tft.fillScreen(ST7735_BLACK);
  
  tft.setCursor(0, 0);
  
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(0);
  tft.println(">>>TEMPERATURE<<<");
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1);
  tft.print("Inside : ");
  
  tft.print(temp);
  tft.println(" [C]\r\n");
    
}












