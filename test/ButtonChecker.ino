// Define button pins
const int buttonPin1 = 26;
const int buttonPin2 = 25;
const int buttonPin3 = 34;
const int buttonPin4 = 39;
const int buttonPin5 = 36;

// Variables to hold the button states
bool buttonState1 = false;
bool buttonState2 = false;
bool buttonState3 = false;
bool buttonState4 = false;
bool buttonState5 = false;

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Initialize the button pins as input with internal pull-down resistors
  pinMode(buttonPin1, INPUT_PULLDOWN);
  pinMode(buttonPin2, INPUT_PULLDOWN);
  pinMode(buttonPin3, INPUT_PULLDOWN);
  pinMode(buttonPin4, INPUT_PULLDOWN);
  pinMode(buttonPin5, INPUT_PULLDOWN);

  // Print a starting message
  Serial.println("Starting button state monitoring...");
}

void loop() {
  // Read the current state of each button
  bool currentButtonState1 = digitalRead(buttonPin1);
  bool currentButtonState2 = digitalRead(buttonPin2);
  bool currentButtonState3 = digitalRead(buttonPin3);
  bool currentButtonState4 = digitalRead(buttonPin4);
  bool currentButtonState5 = digitalRead(buttonPin5);

  // Check if any button state has changed
  if (currentButtonState1 != buttonState1) {
    buttonState1 = currentButtonState1; // Update the state
    Serial.print("Button 1 State: ");
    Serial.println(buttonState1 ? "Pressed" : "Released");
  }

  if (currentButtonState2 != buttonState2) {
    buttonState2 = currentButtonState2; // Update the state
    Serial.print("Button 2 State: ");
    Serial.println(buttonState2 ? "Pressed" : "Released");
  }

  if (currentButtonState3 != buttonState3) {
    buttonState3 = currentButtonState3; // Update the state
    Serial.print("Button 3 State: ");
    Serial.println(buttonState3 ? "Pressed" : "Released");
  }

  if (currentButtonState4 != buttonState4) {
    buttonState4 = currentButtonState4; // Update the state
    Serial.print("Button 4 State: ");
    Serial.println(buttonState4 ? "Pressed" : "Released");
  }

  if (currentButtonState5 != buttonState5) {
    buttonState5 = currentButtonState5; // Update the state
    Serial.print("Button 5 State: ");
    Serial.println(buttonState5 ? "Pressed" : "Released");
  }

  delay(50); // Small delay to debounce
}