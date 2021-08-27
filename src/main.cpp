#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     2
#define LED_COUNT   36

CRGB leds[LED_COUNT];

void setup()
{
    Serial.begin(115200);
    // put your setup code here, to run once:
    delay(3000);
    FastLED.addLeds<SK6812, LED_PIN, RGB>(leds, LED_COUNT);
    FastLED.setBrightness(50);
    Serial.println("lets get the party started");
}

uint8_t actual_led = 0;

void loop()
{
    // put your main code here, to run repeatedly:
    //fill_rainbow();
    // alle LEDS auf schwarz
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds[i] = CRGB::Black;
    }
    // eine LED auf blau
    leds[actual_led] = CRGB::Blue;
    // dann eine LED weitergehen, ggf zum Anfang
    if (++actual_led >= LED_COUNT)
    {
        actual_led = 0;
    }
    FastLED.show();
    FastLED.delay(500);
    //EVERY_N_MILLISECONDS(50) { fill_rainbow(leds, LED_COUNT); }
}