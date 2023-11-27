#include <Arduino.h>
#include <bb_captouch.h>

#define TOUCH_SDA 4
#define TOUCH_SCL 5
#define TOUCH_IRQ 3
#define TOUCH_RST 2

#define TOUCH_MAX_FINGERS 5

#define POWER_EN 1

BBCapTouch touch;

void setup()
{
    Serial.begin(115200);

    // power on screen
    pinMode(POWER_EN, OUTPUT);
    digitalWrite(POWER_EN, HIGH);

    // init touch screen
    touch.init(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_IRQ);
}

void loop()
{
    static bool is_pressed;
    TOUCHINFO points;
    int i;

    if (touch.getSamples(&points)) {
        for (i = 0; i < points.count; i++) {
            Serial.print("X[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(points.x[i]);
            Serial.print(" ");
            Serial.print(" Y[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(points.y[i]);
            Serial.print(" ");
            is_pressed = true;
        }
        Serial.println();
    } else {
        if (is_pressed) {
            Serial.println("Released");
            is_pressed = false;
        }
    }

    // shot delay is required for prevent expected release
    delay(20);
}