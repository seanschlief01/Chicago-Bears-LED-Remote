// Define the input pins
const int button1Pin = 3;
const int button2Pin = 4;
const int button3Pin = 5;
const int button4Pin = 6;
const int button5Pin = 7;

void setup() {
  // Initialize the input pins
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(button5Pin, INPUT);

  // Start the serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the input pins
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  int button4State = digitalRead(button4Pin);
  int button5State = digitalRead(button5Pin);

  // Debugging: print the states of the inputs
  Serial.print("Button 1: "); Serial.println(button1State);
  Serial.print("Button 2: "); Serial.println(button2State);
  Serial.print("Button 3: "); Serial.println(button3State);
  Serial.print("Button 4: "); Serial.println(button4State);
  Serial.print("Button 5: "); Serial.println(button5State);
  Serial.println();

  // Add a small delay to avoid flooding the serial monitor
  delay(1000);
}
