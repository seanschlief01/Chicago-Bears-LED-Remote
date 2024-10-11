#include <esp_system.h>

void setup() {
  Serial.begin(115200);
  
  // Obtain the Bluetooth MAC address
  uint8_t macAddr[6];
  esp_read_mac(macAddr, ESP_MAC_BT);
  
  // Print MAC address
  Serial.print("Bluetooth MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02x", macAddr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}

void loop() {
  // Your code here
}