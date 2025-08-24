#include <FastLED.h>

#ifndef LEDS_H
#define LEDS_H

namespace leds {

class RgbLed {
private:
  CRGB leds[1];

  CRGB *getLeds() const;

public:
  RgbLed(unsigned int brightness);

  ~RgbLed();

  void Off();

  void Red();

  void Green();
};

} // namespace leds

#endif // LEDS_H