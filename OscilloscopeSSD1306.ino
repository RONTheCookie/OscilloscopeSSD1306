
//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define VoltYCursor SCREEN_HEIGHT/1*0.30 // above .61 will go off screen
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # THIS DOESN'T MATTER FOR SOME DISPLAYS
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int sensorPin = A0;    // select the input pin
int sensorValue = 0;  // variable to store the value coming from the sensor
int cw = 0;
int maxv = 0;

void setup() {
//    Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE, BLACK); // Draw white text
//  display.cp437(true);         // Use full 256 char 'Code Page 437' font
}

void loop() {
  // put your main code here, to run repeatedly:
    sensorValue = analogRead(sensorPin);
    if (sensorValue > maxv) maxv = map(sensorValue,0,1023,0,5);
    display.drawPixel(cw, map(sensorValue,0,1023,0,SCREEN_HEIGHT), WHITE);
    if (cw == 1023) {
      display.setCursor(10, VoltYCursor);     // Start at top-left corner
      display.write(maxv);
      display.display();
      display.clearDisplay();
      cw=0;
    }
    cw++;
}
