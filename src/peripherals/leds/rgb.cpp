#include <FastLED.h>

#include "rgb.h"

namespace leds {

CRGB *RgbLed::getLeds() const { return (CRGB *)this->leds; }

RgbLed::RgbLed(unsigned int brightness) {
  FastLED.addLeds<WS2812B, 2, GRB>(leds, 1);
  FastLED.setBrightness(brightness);
  FastLED.clear();
  FastLED.show();
}

RgbLed::~RgbLed() {
  this->Off();
  FastLED.clear();
}

void RgbLed::Off() {
  CRGB *leds = this->getLeds();
  leds[0] = CRGB::Black;
  FastLED.show();
}

void RgbLed::Red() {
  CRGB *leds = this->getLeds();
  leds[0] = CRGB::Red;
  FastLED.show();
}

void RgbLed::Green() {
  CRGB *leds = this->getLeds();
  leds[0] = CRGB::Green;
  FastLED.show();
}

} // namespace leds