#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 2

CRGB leds[NUM_LEDS];
CRGB navyBlue = CRGB(0, 10, 42);
CRGB orange = CRGB(165, 56, 0);
int currentEffect = 0;

// Define buttons
#define BUTTON_1_PIN 3
#define BUTTON_2_PIN 4
#define BUTTON_3_PIN 5
#define BUTTON_4_PIN 6
#define BUTTON_5_PIN 7

// Button state flags
bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;
bool button4Pressed = false;
bool button5Pressed = false;

// State variables for effects
uint8_t colorWaveIndex = 0;
unsigned long lastColorWaveUpdate = 0;
unsigned long lastPulseUpdate = 0;
bool pulseDirection = true;
uint8_t pulseBrightness = 0;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  // Initialize buttons with internal pull-up resistors
  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);
  pinMode(BUTTON_3_PIN, INPUT);
  pinMode(BUTTON_4_PIN, INPUT);
  pinMode(BUTTON_5_PIN, INPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("Setup complete.");
}

void loop() {
  // Check for button presses
  if (digitalRead(BUTTON_1_PIN) == HIGH && !button1Pressed) {
    currentEffect = 1;
    Serial.println("Button 1 pressed. Effect set to Bears Color Wave.");
    button1Pressed = true;
  } else if (digitalRead(BUTTON_1_PIN) == LOW && button1Pressed) {
    button1Pressed = false;
  }

  if (digitalRead(BUTTON_2_PIN) == HIGH && !button2Pressed) {
    currentEffect = 2;
    Serial.println("Button 2 pressed. Effect set to Bears Chase.");
    button2Pressed = true;
  } else if (digitalRead(BUTTON_2_PIN) == LOW && button2Pressed) {
    button2Pressed = false;
  }

  if (digitalRead(BUTTON_3_PIN) == HIGH && !button3Pressed) {
    currentEffect = 3;
    Serial.println("Button 3 pressed. Effect set to Bears Sparkle.");
    button3Pressed = true;
  } else if (digitalRead(BUTTON_3_PIN) == LOW && button3Pressed) {
    button3Pressed = false;
  }

  if (digitalRead(BUTTON_4_PIN) == HIGH && !button4Pressed) {
    currentEffect = 4;
    Serial.println("Button 4 pressed. Effect set to Bears Pulse.");
    button4Pressed = true;
  } else if (digitalRead(BUTTON_4_PIN) == LOW && button4Pressed) {
    button4Pressed = false;
  }

  if (digitalRead(BUTTON_5_PIN) == HIGH && !button5Pressed) {
    currentEffect = 0;
    Serial.println("Button 5 pressed. Effect set to All Black.");
    button5Pressed = true;
  } else if (digitalRead(BUTTON_5_PIN) == LOW && button5Pressed) {
    button5Pressed = false;
  }

  // Run the chosen LED effect
  switch (currentEffect) {
    case 1:
      bearsColorWave();
      break;
    case 2:
      bearsChase();
      break;
    case 3:
      bearsSparkle();
      break;
    case 4:
      bearsPulse();
      break;
    default:
      allBlack();
      break;
  }
}

void allBlack() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void bearsColorWave() {
  if (millis() - lastColorWaveUpdate >= 50) {
    for (int i = 0; i < NUM_LEDS; i++) {
      uint8_t brightnessBlue = sin8(colorWaveIndex + i * 8);
      uint8_t brightnessOrange = sin8(colorWaveIndex + 128 + i * 8);

      leds[i] = CRGB(
        (navyBlue.r * brightnessBlue + orange.r * brightnessOrange) / 255,
        (navyBlue.g * brightnessBlue + orange.g * brightnessOrange) / 255,
        (navyBlue.b * brightnessBlue + orange.b * brightnessOrange) / 255
      );
    }
    FastLED.show();
    colorWaveIndex++;
    lastColorWaveUpdate = millis();
  }
}

void bearsChase() {
  static int pos = 0;
  pos = (pos + 1) % NUM_LEDS;
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for (int i = 0; i < 50; i++) {
    leds[(pos + i) % NUM_LEDS] = (i < 25) ? navyBlue : orange;
  }
  FastLED.show();
}

void bearsSparkle() {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  for (int i = 0; i < 10; i++) {
    leds[random(NUM_LEDS)] = (random(2) == 0) ? navyBlue : orange;
  }
  FastLED.show();
}

void bearsPulse() {
  if (millis() - lastPulseUpdate >= 50) {
    for (int i = 0; i < NUM_LEDS; i++) {
      uint8_t brightness = pulseBrightness;
      leds[i] = CRGB(
        (navyBlue.r * (255 - brightness) + orange.r * brightness) / 255,
        (navyBlue.g * (255 - brightness) + orange.g * brightness) / 255,
        (navyBlue.b * (255 - brightness) + orange.b * brightness) / 255
      );
    }
    FastLED.show();

    if (pulseDirection) {
      pulseBrightness += 5;
      if (pulseBrightness >= 255) {
        pulseBrightness = 255;
        pulseDirection = false;
      }
    } else {
      pulseBrightness -= 5;
      if (pulseBrightness <= 0) {
        pulseBrightness = 0;
        pulseDirection = true;
      }
    }

    lastPulseUpdate = millis();
  }
}
