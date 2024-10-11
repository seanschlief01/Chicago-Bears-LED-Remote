#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define LED_BT_GREEN 4   // GPIO 4 for green LED

const int button1Pin = 13;
const int button2Pin = 27;
const int button3Pin = 33;
const int button4Pin = 15;
const int button5Pin = 32;

unsigned long previousMillis;
bool MasterConnected;
String device_name = "ESP32-BT-Slave";
String MACadd = "e0:5a:1b:58:c6:02";

void Bt_Status(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("Server Connected");
    digitalWrite(LED_BT_GREEN, HIGH);
    MasterConnected = true;
  } else if (event == ESP_SPP_CLOSE_EVT) {
    Serial.println("Server Disconnected");
    digitalWrite(LED_BT_GREEN, LOW);
    MasterConnected = false;
  }
}

void setup() {
  pinMode(LED_BT_GREEN, OUTPUT);
  pinMode(button1Pin, OUTPUT);
  pinMode(button2Pin, OUTPUT);
  pinMode(button3Pin, OUTPUT);
  pinMode(button4Pin, OUTPUT);
  pinMode(button5Pin, OUTPUT);
  Serial.begin(115200);

  SerialBT.register_callback(Bt_Status);
  SerialBT.begin(device_name);

  Serial.printf("Device \"%s\" started. Waiting for connection...\n", device_name.c_str());
}

void loop() {
  if (!MasterConnected) {
    // Blink LED to indicate waiting for connection
    if (millis() - previousMillis >= 500) {
      previousMillis = millis();
      digitalWrite(LED_BT_GREEN, !digitalRead(LED_BT_GREEN));
    }
  }

  // Data send/receive via Bluetooth
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();
    Serial.print("Received Button ");
    Serial.println(receivedChar);

    switch (receivedChar) {
      case '1':
        digitalWrite(button1Pin, HIGH);
        delay(1000);  // Short delay to ensure the pulse is detected
        digitalWrite(button1Pin, LOW);
        break;
      case '2':
        digitalWrite(button2Pin, HIGH);
        delay(1000);
        digitalWrite(button2Pin, LOW);
        break;
      case '3':
        digitalWrite(button3Pin, HIGH);
        delay(1000);
        digitalWrite(button3Pin, LOW);
        break;
      case '4':
        digitalWrite(button4Pin, HIGH);
        delay(1000);
        digitalWrite(button4Pin, LOW);
        break;
      case '5':
        digitalWrite(button5Pin, HIGH);
        delay(1000);
        digitalWrite(button5Pin, LOW);
        break;
      default:
        // Turn off all outputs if an unexpected character is received
        digitalWrite(button1Pin, LOW);
        digitalWrite(button2Pin, LOW);
        digitalWrite(button3Pin, LOW);
        digitalWrite(button4Pin, LOW);
        digitalWrite(button5Pin, LOW);
        break;
    }
  }
}