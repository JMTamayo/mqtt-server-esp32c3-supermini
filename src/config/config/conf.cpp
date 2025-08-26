#include "conf.h"

namespace config {

const unsigned long DEFAULT_BAUD_RATE = 921600;

const unsigned int LED_BRIGHTNESS = 255;

const char *WIFI_SSID = "JMTamayo-2.4G"; // Replace with your real WiFi SSID

const char *WIFI_PASSWORD =
    "3ahY21me.31"; // Replace with your real WiFi password

const char *WIFI_HOSTNAME = "home-mqtt-broker";

const unsigned long WIFI_MAX_RETRY_TIME_MS = 30000;

} // namespace config