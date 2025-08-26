#include <PicoMQTT.h>

#include "config/config/conf.h"
#include "config/logging/logger.h"

#include "peripherals/leds/rgb.h"
#include "services/wifi/wifi.h"

leds::RgbLed *rgbLed;
wifi_service::WifiService *wifi;
PicoMQTT::Server *mqtt;

void setup() {
  logging::logger->Initialize();
  logging::logger->Info("Setting up system");

  rgbLed = new leds::RgbLed(config::LED_BRIGHTNESS);

  wifi = new wifi_service::WifiService(config::WIFI_SSID, config::WIFI_PASSWORD,
                                       config::WIFI_HOSTNAME,
                                       config::WIFI_MAX_RETRY_TIME_MS, rgbLed);
  wifi->Connect();

  mqtt = new PicoMQTT::Server();
  mqtt->begin();

  logging::logger->Info("System setup complete");
}

void loop() {
  if (!wifi->IsConnected()) {
    wifi->Connect();
  }
  mqtt->loop();
}