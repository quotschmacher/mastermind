#include <Arduino.h>
#include <FastLED.h>
#include <color_chooser.hpp>

#define LED_PIN     23
#define LED_COUNT   36
#define LED_ON      18
//test
CRGB leds[LED_COUNT];

// Funktionsprototypen
void iterate_colors_loop();

void setup()
{
    Serial.begin(115200);
    // put your setup code here, to run once:
    delay(3000);
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(50);
    Serial.println("lets get the party started");
    pinMode(LED_ON,OUTPUT);
    digitalWrite(LED_ON,HIGH);

}

uint8_t actual_led = 0;

void loop()
{
    iterate_colors_loop();

    // put your main code here, to run repeatedly:
    //fill_rainbow();
    // alle LEDS auf schwarz
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds[i] = CRGB::Black;
    }
    // eine LED auf blau
    leds[actual_led] = CRGB::Green;
    // dann eine LED weitergehen, ggf zum Anfang
    if (++actual_led >= LED_COUNT)
    {
        actual_led = 0;
    }
    FastLED.show();
    FastLED.delay(250);
    //EVERY_N_MILLISECONDS(50) { fill_rainbow(leds, LED_COUNT); }
}

void iterate_colors_loop()
{
    // alle LEDS auf schwarz
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds[i] = CRGB::Black;
    }
    while (1)
    {
        leds[0] = ColorChooser::getNextColor(leds[0]);
        FastLED.show();
        FastLED.delay(500);
    }
}
