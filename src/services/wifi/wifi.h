#include <WiFi.h>

#include "peripherals/leds/rgb.h"

#ifndef WIFI_H
#define WIFI_H

namespace wifi_service {

class WifiService {
private:
  const char *ssid;
  const char *password;
  const char *hostname;

  leds::RgbLed *indicator;

  const char *getSsid() const;

  const char *getPassword() const;

  const char *getHostname() const;

  leds::RgbLed *getIndicator();

public:
  WifiService(const char *ssid, const char *password, const char *hostname,
              leds::RgbLed *indicator);

  ~WifiService();

  void Connect();

  bool IsConnected();
};

} // namespace wifi_service

#endif // WIFI_H