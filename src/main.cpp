#include <Arduino.h>
#include <FastLED.h>
#include <color_chooser.hpp>
#include <settings.h>
#include <WiFi.h>
#include <ESP32Encoder.h>

#define LED_PIN     23
#define LED_COUNT   36
#define LED_ON      18
#define BRIGHTNESS  1

CRGB leds[LED_COUNT];
ESP32Encoder encoder;

// Funktionsprototypen
void iterate_colors_loop();
void init_rotary_encoders();


void setup()
{
    //randomSeed(analogRead(0));
    uint32_t rnd_num = random(USED_COLORS);
    Serial.begin(115200);
    Serial.println(rnd_num);
    // put your setup code here, to run once:
    delay(3000);
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(BRIGHTNESS);
    Serial.println("lets get the party started");
    pinMode(LED_ON,OUTPUT);
    digitalWrite(LED_ON,HIGH);

    
    WiFi.disconnect();
    WiFi.setHostname(HOSTNAME);
    WiFi.mode(WIFI_STA);
    delay(100);

    Serial.println("Connecting to Wifi");

    
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    int cnt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        cnt++;
        if (cnt > 10)
        {
            WiFi.begin(WLAN_SSID, WLAN_PASS);
            cnt = 0;
        }
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);
    init_rotary_encoders();
}

uint8_t actual_led = 0;

void loop()
{
    iterate_colors_loop();

    // put your main code here, to run repeatedly:
    //fill_rainbow();
    // alle LEDS auf schwarz
    for (int i = 1; i < LED_COUNT; i++)
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

    int64_t cnt = encoder.getCount();
    if (cnt > 0)
    {
        leds[0] = ColorChooser::getNextColor(leds[0]);
    }
    else if (cnt < 0)
    {
        leds[0] = ColorChooser::getPreviousColor(leds[0]);
    }

    FastLED.show();
    FastLED.delay(250);

    //EVERY_N_MILLISECONDS(50) { fill_rainbow(leds, LED_COUNT); }
}


void iterate_colors_loop()
{
    // alle LEDS auf schwarz
    for (int i = 1; i < LED_COUNT; i++)
    {
        leds[i] = CRGB::Black;
    }
    
while (1)
    {
       for (uint8_t i = 0; i < LED_COUNT; i++)
       {
        leds[i] = ColorChooser::getNextColor(leds[i]);
        FastLED.show();
        FastLED.delay(20);           
       }
    }
}


void init_rotary_encoders()
{
    // hardware-pullups
	//ESP32Encoder::useInternalWeakPullResistors=DOWN;
	// Enable the weak pull up resistors
	//ESP32Encoder::useInternalWeakPullResistors=UP;
    encoder.attachHalfQuad(14, 27);
}
