#ifndef LED_H
#define LED_H

#include <FastLED.h>
#include "Config.h"

extern CRGB leds[NUM_LEDS]; 

void initLed();
void ledOn(CRGB color);

#endif