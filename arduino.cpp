#include <Servo.h>

// Pin Definitions
const int neutralLight = 2;
const int neutralInput = 4;
const int servoPin = 9;
const int relayPin = 6;
const int ignitionLight = 5;
const int espInputPin = 3;
const int parkingBreakLed = 10;

// Servo object
Servo myServo;

// Function prototypes
void setup();
void loop();
void startEngine();
void rotateServo();
void stopEngine();

void setup() {
  pinMode(neutralLight, OUTPUT);
  pinMode(neutralInput, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(ignitionLight, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(espInputPin, INPUT);
  pinMode(parkingBreakLed, OUTPUT);

  myServo.attach(servoPin);
}

void loop() {
  if (digitalRead(espInputPin) == HIGH) {
    startEngine();
    rotateServo();
    stopEngine();
  } else {
    digitalWrite(ignitionLight, LOW);
    digitalWrite(neutralLight, LOW);
    digitalWrite(relayPin, HIGH);
    digitalWrite(parkingBreakLed, LOW);
  }
}

void startEngine() {
  delay(1000);
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(ignitionLight, 1);
  delay(1000);
}

void rotateServo() {
  if (digitalRead(ignitionLight) == HIGH) {
    delay(1000);
    myServo.write(0);
    digitalWrite(relayPin, HIGH);

    if (digitalRead(neutralInput) == LOW) {
      digitalWrite(relayPin, HIGH);
      delay(1000);

      myServo.write(180);
      delay(1000);
      digitalWrite(parkingBreakLed, HIGH);
      delay(2000);

      myServo.write(90);
      delay(2000);

      delay(2000);

      digitalWrite(neutralLight, HIGH);
      delay(2000);
      digitalWrite(relayPin, LOW);
    } else {
      delay(2000);
      digitalWrite(relayPin, LOW);
    }

    for (int i = 0; i < 60; i++) {
      if (digitalRead(espInputPin) == HIGH) {
        delay(1000);
      } else {
        digitalWrite(relayPin, HIGH);
        myServo.write(0);
        delay(1000);
        digitalWrite(neutralLight, LOW);
        digitalWrite(parkingBreakLed, LOW);
        delay(1000);
        digitalWrite(ignitionLight, LOW);
      }
    }
  } else {
    digitalWrite(neutralLight, LOW);
    delay(100);
    digitalWrite(relayPin, HIGH);
    myServo.write(0);
    digitalWrite(parkingBreakLed, LOW);
  }
}

void stopEngine() {
  digitalWrite(ignitionLight, LOW);
  digitalWrite(neutralLight, LOW);
  digitalWrite(relayPin, HIGH);
  digitalWrite(parkingBreakLed, LOW);
}
