#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define LED_BT_GREEN 32    // GPIO 4 for blue LED
#define LED_BT_RED 14    // GPIO 21 for red LED

unsigned long previousMillisReconnect;
bool SlaveConnected;
int recatt = 0;

String myName = "ESP32-BT-Master";
String slaveName = "ESP32-BT-Slave";
uint8_t address[6] = {0xe0, 0x5a, 0x1b, 0x58, 0xc6, 0x16}; // Slave's MAC address

// Define GPIO pins for buttons
const int buttonPins[] = {4, 36, 39, 34, 25};
const int numButtons = 5;

// Array to store the previous state of each button
bool buttonStates[numButtons];

void Bt_Status(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_OPEN_EVT) {
    Serial.println("Client Connected");
    digitalWrite(LED_BT_GREEN, HIGH);
    digitalWrite(LED_BT_RED, LOW);
    SlaveConnected = true;
    recatt = 0;
  } else if (event == ESP_SPP_CLOSE_EVT) {
    Serial.println("Client Disconnected");
    digitalWrite(LED_BT_RED, HIGH);
    digitalWrite(LED_BT_GREEN, LOW);
    SlaveConnected = false;
  }
}

void setup() {
  pinMode(LED_BT_GREEN, OUTPUT);
  pinMode(LED_BT_RED, OUTPUT);
  digitalWrite(LED_BT_RED, HIGH);
  SlaveConnected = false;
  Serial.begin(115200);

  SerialBT.register_callback(Bt_Status);
  SerialBT.begin(myName, true); // Start as server (master)
  Serial.printf("Device \"%s\" started in master mode. Waiting for connection...\n", myName.c_str());

  // Initialize buttons pins as input with internal pull-down resistor
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLDOWN);
    buttonStates[i] = LOW; // Intialize previous state as LOW (not pressed)
  }

  // Attempt to connect to Slave
  SerialBT.connect(address);
}

void loop() {
  if (!SlaveConnected) {
    if (millis() - previousMillisReconnect >= 10000) {
      previousMillisReconnect = millis();
      recatt++;
      Serial.print("Trying to reconnect. Attempt No.: ");
      Serial.println(recatt);
      Serial.println("Stopping Bluetooth...");
      SerialBT.end();
      Serial.println("Bluetooth stopped !");
      Serial.println("Starting Bluetooth...");
      SerialBT.begin(myName, true);
      Serial.printf("Device \"%s\" started in master mode. Waiting for connection...\n", myName.c_str());
      SerialBT.connect(address);
    }
  }

  // Check button presses and send signals via Bluetooth
  for (int i = 0; i < numButtons; i++) {
    bool currentState = digitalRead(buttonPins[i]);
    if (currentState == HIGH && buttonStates[i] == LOW) {
      // Button press detected
      Serial.print("Button ");
      Serial.print(i + 1);
      Serial.println(" pressed");

      // Send a unique signal to the Slave based on which button is pressed
      SerialBT.write('1' + i); // Send 'A' for button 0, 'B' for button 1, etc.

      // Update button state
      buttonStates[i] = HIGH;
    } else if (currentState == LOW && buttonStates[i] == HIGH) {
      // Button released
      buttonStates[i] = LOW;
    }
  }
  delay(20);
}