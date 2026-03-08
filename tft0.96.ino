#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <animation.h>

#define OLED_SDA 3
#define OLED_SCL 4
#define SCREEN_HEIGH 64
#define SCREEN_WIDTH 128 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGH, &Wire, -1);

unsigned long Time = 0;
int bufferAnimationIndex = 0;     //index of frame
int bufferAnimationFPS = 30;      //setting fps for animation

void setup() {
  Wire.begin(OLED_SDA, OLED_SCL);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No signal!");
    while(true);
  }

  display.clearDisplay();
}

void loop() {
  if (millis() - Time >= (int)(1000/bufferAnimationFPS)) {
    Time = millis();
    display.clearDisplay();
    display.drawBitmap(0, 0, bufferAnimation[bufferAnimationIndex], 128, 64, SSD1306_WHITE);
    display.display();
    bufferAnimationIndex ++;
    if (bufferAnimationIndex >= 214) bufferAnimationIndex = 0;
  }
}