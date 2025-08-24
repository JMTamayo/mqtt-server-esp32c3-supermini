#include "wifi.h"

#include "config/logging/logger.h"

namespace wifi_service {

const char *WifiService::getSsid() const { return this->ssid; }

const char *WifiService::getPassword() const { return this->password; }

const char *WifiService::getHostname() const { return this->hostname; }

leds::RgbLed *WifiService::getIndicator() { return this->indicator; }

WifiService::WifiService(const char *ssid, const char *password,
                         const char *hostname, leds::RgbLed *indicator)
    : ssid(ssid), password(password), hostname(hostname), indicator(indicator) {
}

WifiService::~WifiService() {}

void WifiService::Connect() {
  this->indicator->Red();

  WiFi.begin(this->getSsid(), this->getPassword());

  WiFi.setHostname(this->getHostname());
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  logging::logger->Debug("Connecting to WiFi network: " +
                         String(this->getSsid()));

  while (!this->IsConnected()) {
    logging::logger->Warning("Connection status: " + String(WiFi.status()));
    delay(500);
  }

  logging::logger->Debug("Connection successfully established");
  logging::logger->Debug("IP: " + String(WiFi.localIP().toString().c_str()));
  logging::logger->Debug("Hostname: " + String(WiFi.getHostname()));

  this->indicator->Green();
}

bool WifiService::IsConnected() { return WiFi.status() == WL_CONNECTED; }

} // namespace wifi_service