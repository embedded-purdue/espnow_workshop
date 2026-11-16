/*
 * =========================================================================
 * STEP 1: ESP32 MAC Address Finder & I2C Screen Checker
 * =========================================================================
 * Upload this first! Open the Serial Monitor (115200 baud) and press the
 * EN / RST button on your ESP32 to see:
 * 1. Your ESP32's MAC address (ready to copy-paste for your partner team)
 * 2. Your 1602 LCD's I2C address (usually 0x27 or 0x3F)
 * =========================================================================
 */

#include <WiFi.h>
#include <Wire.h>
#include <esp_wifi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Put the Wi-Fi radio in Station mode so we can read its hardware MAC address
  WiFi.mode(WIFI_STA);

  // Read the 6-byte MAC address directly from the ESP32 hardware
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);

  Serial.println("\n==========================================");
  if (ret == ESP_OK) {
    // 1. Standard format (e.g., 5c:01:3b:9c:78:c0)
    Serial.print("Your MAC Address:   ");
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);

    // 2. Copy-paste C array format for the other team's code!
    Serial.print("Copy-Paste Array:   {");
    Serial.printf("0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
    Serial.println("}");
  } else {
    Serial.println("Failed to read MAC address.");
  }

  // 3. Scan I2C pins (SDA = 21, SCL = 22) to verify the 1602 LCD wiring
  Wire.begin(21, 22);
  bool foundLCD = false;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("LCD I2C Address:    0x");
      Serial.println(address, HEX);
      foundLCD = true;
    }
  }
  if (!foundLCD) {
    Serial.println("LCD I2C Address:    NOT FOUND (Check SDA=21, SCL=22, VCC=VIN, GND=GND)");
  }
  Serial.println("==========================================");
}

void loop() {
  // Nothing needed here—press the EN/RST button on the ESP32 to print again!
}