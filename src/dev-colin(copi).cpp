#include <Arduino.h>

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5
#define BUTTON5 6
#define BUTTON6 7
#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define LED5 12
#define LED6 13
#define numLeds 6

const int BUTTONS[numLeds] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4, BUTTON5, BUTTON6};
const int LEDS[numLeds] = {LED1, LED2, LED3, LED4, LED5, LED6};

bool ledState[numLeds];
bool buttonState[numLeds];
bool lastButtonState[numLeds];

unsigned long lastDebounceTime[numLeds];
const unsigned long debounceDelay = 50;


// put function declarations here:
void randomizeLedStates();


void setup() {

  for (int i = 0; i < numLeds; i++)
  {
    pinMode(BUTTONS[i], INPUT_PULLUP);
    pinMode(LEDS[i], OUTPUT);
    lastButtonState[i] = false;
    lastDebounceTime[i] = 0;
  }

  randomizeLedStates();

}


void loop() {

  for (int i = 0; i < numLeds; i++)
  {
    bool currentButtonPressed = digitalRead(BUTTONS[i]);

    if (currentButtonPressed != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }

    if (millis() - lastDebounceTime[i] > debounceDelay) {
      if (currentButtonPressed != buttonState[i]) {
        buttonState[i] = currentButtonPressed;
        if (currentButtonPressed == true) {
          ledState[i] = !ledState[i];
        }
      }
    }

    lastButtonState[i] = currentButtonPressed;

    digitalWrite(LEDS[i], !ledState[i]);
  }
}


void randomizeLedStates() {

  for (int i = 0; i < numLeds; i++)
  {
    randomSeed(analogRead(0));
    ledState[i] = random(0, 2);
  }

}