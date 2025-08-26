#include "wifi.h"

#include "config/logging/logger.h"

namespace wifi_service {

const char *WifiService::getSsid() const { return this->ssid; }

const char *WifiService::getPassword() const { return this->password; }

const char *WifiService::getHostname() const { return this->hostname; }

unsigned long WifiService::getMaxRetryTimeMs() const {
  return this->maxRetryTimeMs;
}

leds::RgbLed *WifiService::getIndicator() { return this->indicator; }

WifiService::WifiService(const char *ssid, const char *password,
                         const char *hostname, unsigned long maxRetryTimeMs,
                         leds::RgbLed *indicator)
    : ssid(ssid), password(password), hostname(hostname),
      maxRetryTimeMs(maxRetryTimeMs), indicator(indicator) {}

WifiService::~WifiService() {}

void WifiService::Connect() {
  this->indicator->Red();

  WiFi.begin(this->getSsid(), this->getPassword());

  WiFi.setHostname(this->getHostname());
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  logging::logger->Debug("Connecting to WiFi network: " +
                         String(this->getSsid()));

  unsigned long startTimeMs = millis();
  unsigned long retryTimeMs = 0;

  while (!this->IsConnected()) {
    if (retryTimeMs >= this->getMaxRetryTimeMs()) {
      logging::logger->Error(
          "Connection to WiFi network failed. Restarting the device.");

      this->indicator->Off();
      ESP.restart();
    }

    logging::logger->Warning(
        "WiFi connection not established. Status: " + String(WiFi.status()) +
        ". Retry time [ms]: " + String(retryTimeMs));

    delay(500);
    retryTimeMs = millis() - startTimeMs;
  }

  logging::logger->Debug("Connection successfully established");
  logging::logger->Debug("IP: " + String(WiFi.localIP().toString().c_str()));
  logging::logger->Debug("Hostname: " + String(WiFi.getHostname()));

  this->indicator->Green();
}

bool WifiService::IsConnected() { return WiFi.status() == WL_CONNECTED; }

} // namespace wifi_service