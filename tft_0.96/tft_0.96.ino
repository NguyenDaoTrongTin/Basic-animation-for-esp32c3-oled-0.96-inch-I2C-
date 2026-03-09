#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "animation.h"

#define OLED_SDA 3
#define OLED_SCL 4

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

uint8_t frameBuffer[1024];   // SSD1306 buffer
uint16_t FRAMECOUNT1;
uint16_t FRAMECOUNT2;
uint16_t FRAMECOUNT3;

unsigned long lastFrameTime = 0;

uint16_t frameIndex = 0;
uint8_t animationIndex = 0;
uint8_t frameCountIndex = 0;
uint8_t animationFPS = 30;


void decodeFrame(const uint8_t* data)
{
    uint16_t i = 0;
    uint16_t pos = 0;

    while (true)
    {
        uint8_t count = pgm_read_byte(&data[i++]);

        if (count == 0) break;

        uint8_t value = pgm_read_byte(&data[i++]);

        while (count--)
        {
            frameBuffer[pos++] ^= value;

            if (pos >= 1024)
                return;
        }
    }
}


void drawAnimation()
{

    decodeFrame(bufferAnimation[animationIndex][frameIndex]);

    display.clearDisplay();

    display.drawBitmap(
        0,
        0,
        frameBuffer,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SSD1306_WHITE
    );

    display.display();

    frameIndex++;
    if (frameIndex >= FRAME_COUNT[frameCountIndex]) {
        frameIndex = 0;
        animationIndex ++;
        frameCountIndex ++;
        memset(frameBuffer, 0, sizeof(frameBuffer));

        if (frameCountIndex >= 3){
          animationIndex = 0;
          frameCountIndex = 0;
        };
    }
}


void setup()
{
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.begin(115200);
        Serial.println("SSD1306 not found");
        while (true);
    }

    memset(frameBuffer, 0, sizeof(frameBuffer));

    display.clearDisplay();
    display.display();
}


void loop()
{
    if (millis() - lastFrameTime >= (1000 / animationFPS))
    {
        lastFrameTime = millis();

        drawAnimation();
    }
}