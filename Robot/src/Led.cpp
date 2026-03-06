#include "Led.h"

CRGB leds[NUM_LEDS]; 

void initLed() {
    FastLED.addLeds<NEOPIXEL, PIN_RBGLED>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
}

void ledOn(CRGB color) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color; 
  }
  FastLED.show(); 
}