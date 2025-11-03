/*
 * RobooLed - Animated OLED Eyes for Arduino
 * Copyright (C) 2025 Pedro Pacheco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

#define i2c_Address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define ON true
#define OFF false

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RoboEyes<Adafruit_SSD1306> roboEyes(display);

unsigned long randomNumber = 0;
unsigned long now = 0;

void setup()
{
    Serial.begin(9600);

    randomSeed(analogRead(A0));

    if (!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
    roboEyes.setAutoblinker(ON, 6, 3);
    roboEyes.setIdleMode(ON, 5, 1);

    roboEyes.setWidth(36, 36);
    roboEyes.setHeight(20, 20);
    roboEyes.setBorderradius(8, 8);
    roboEyes.setSpacebetween(20);

    switch (random(0, 11))
    {
    case 0:
        angry();
        break;
    case 1:
        angry();
        up();
        break;
    default:
        wakeUp();
        break;
    }
}

void wakeUp()
{
    roboEyes.confusedAnimationDuration = 600;
    roboEyes.setHFlicker(ON, 100);
    roboEyes.anim_confused();
    roboEyes.setIdleMode(ON, 1, 0);
    now = millis();
    while (millis() <= now + 5000)
    {
        roboEyes.blink();
        roboEyes.update();
    }
    roboEyes.setPosition(DEFAULT);
    roboEyes.setIdleMode(ON, 5, 1);
}

void angry()
{
    roboEyes.setMood(ANGRY);
    roboEyes.setIdleMode(ON, 2, 2);
    SecsUpdate(12);

    roboEyes.setPosition(S);
    SecsUpdate(1);

    roboEyes.setIdleMode(ON, 5, 1);
    roboEyes.setMood(DEFAULT);
}

void tired()
{
    roboEyes.setMood(TIRED);
    SecsUpdate(14);
    roboEyes.setMood(DEFAULT);
}

void sweat()
{
    roboEyes.setSweat(ON);
    SecsUpdate(7);
    roboEyes.setSweat(OFF);
}

void shake()
{
    roboEyes.setIdleMode(ON, 1, 2);
    roboEyes.setHFlicker(ON, 1);
    SecsUpdate(15);
    roboEyes.setIdleMode(ON, 5, 1);
    roboEyes.setHFlicker(OFF, 1);
}

void help()
{
    writeMessage("Socorro!\n       Me ajuda!", 40, 22, 1);
    delay(3000);

    writeMessage("Me tira daqui!!!", 40, 22, 1);
    delay(3000);
}

void oneEye()
{
    roboEyes.setCyclops(ON);
    SecsUpdate(9);

    roboEyes.setPosition(DEFAULT);
    SecsUpdate(1);

    roboEyes.setCyclops(OFF);
}

void dead()
{
    writeMessage("X.X", 30, 17, 4);
    delay(20000);
}

void up()
{
    roboEyes.setIdleMode(OFF, 2, 2);
    roboEyes.setPosition(N);
    SecsUpdate(7);
    roboEyes.setIdleMode(ON, 5, 1);
}

void glitch()
{
    writeMessage("❤️😁🤷‍♂️😎", 0, 0, 3);
    delay(7000);
}

void yes()
{
    roboEyes.setIdleMode(OFF, 2, 2);
    for (int i = 0; i < 4; i++)
    {
        roboEyes.setPosition(N);
        SecsUpdate(0.3);
        roboEyes.setPosition(S);
        SecsUpdate(0.3);
    }
    roboEyes.setIdleMode(ON, 5, 1);
}

void no()
{
    roboEyes.setIdleMode(OFF, 2, 2);
    for (int i = 0; i < 4; i++)
    {
        roboEyes.setPosition(W);
        SecsUpdate(0.3);
        roboEyes.setPosition(E);
        SecsUpdate(0.3);
    }
    roboEyes.setIdleMode(ON, 5, 1);
}

void SecsUpdate(float secs)
{
    unsigned long whenStop = millis() + secs * 1000;
    while (millis() <= whenStop)
    {
        roboEyes.update();
    }
}

void writeMessage(String Message, int x, int y, int textSize)
{
    display.clearDisplay();
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(Message);
    display.display();
}

void loop()
{
    SecsUpdate(15);
    
    now = millis();
    randomNumber = random(1, 101);

    if (randomNumber >= 30)
    {
        if (randomNumber <= 40)
        {
            angry();
        }
        else if (randomNumber <= 48)
        {
            tired();
        }
        else if (randomNumber <= 53)
        {
            sweat();
        }
        else if (randomNumber <= 63)
        {
            shake();
        }
        else if (randomNumber <= 68)
        {
            help();
        }
        else if (randomNumber <= 78)
        {
            oneEye();
        }
        else if (randomNumber <= 83)
        {
            dead();
        }
        else if (randomNumber <= 86)
        {
            up();
        }
        else if (randomNumber <= 96)
        {
            glitch();
        }
        else if (randomNumber <= 98)
        {
            yes();
        }
        else
        {
            no();
        }
    }
}
