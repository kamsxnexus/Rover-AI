/*
  Smart Mars Rover AI - Obstacle Avoidance
  ----------------------------------------
  Reads distance from an ultrasonic sensor (HC-SR04) using the NewPing
  library, and drives two DC motors via an L298N/L293D motor driver.

  Behavior:
    - If an obstacle is closer than 20 cm -> stop, turn right, then continue.
    - Otherwise -> move forward.

  This is the "reflex" layer of the rover. The Q-learning logic (see
  python/q_learning_rover.py) is trained separately; this sketch is the
  hardware-side behavior it will eventually be adapted to follow.

  Library required: NewPing
  (Arduino IDE -> Sketch -> Include Library -> Manage Libraries -> search "NewPing")
*/

#include <NewPing.h>

// ---- Ultrasonic sensor pins ----
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200   // Max distance we care about, in cm

// ---- Motor driver pins ----
#define ENA 5   // Left motor speed (PWM)
#define ENB 6   // Right motor speed (PWM)
#define IN1 7   // Left motor direction pin 1
#define IN2 8   // Left motor direction pin 2
#define IN3 11  // Right motor direction pin 1
#define IN4 12  // Right motor direction pin 2

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  delay(50); // NewPing recommends a small delay between pings

  int distance = sonar.ping_cm();
  Serial.println(distance); // Useful for debugging over Serial Monitor

  if (distance > 0 && distance < 20) {
    stopMotors();
    delay(300);
    turnRight();
    delay(500);
  } else {
    moveForward();
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
