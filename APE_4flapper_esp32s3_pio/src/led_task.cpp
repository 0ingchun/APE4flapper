#include "led_task.h"

#define digital_LED_PIN 2

#define LEDS_COUNT  8
#define LEDS_PIN	48
#define CHANNEL		0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void led_task(void *p_led_task)
{
    pinMode(digital_LED_PIN, OUTPUT);

    strip.begin();
    strip.setBrightness(20);

    while (1)
    {
        for (int j = 0; j < 255; j += 2) {

            for (int i = 0; i < LEDS_COUNT; i++) {
                strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
            }

        strip.show();
        delay(8);
        }
        
        digitalWrite(digital_LED_PIN, HIGH);

        vTaskDelay(500);

        digitalWrite(digital_LED_PIN, LOW);

        vTaskDelay(500);
    }
    
}