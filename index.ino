#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int M1_IN1 = 2;
const int M1_IN2 = 3;

const int M2_IN1 = 4;
const int M2_IN2 = 5;

const int M3_IN1 = 6;
const int M3_IN2 = 7;

const int M4_IN1 = 8;
const int M4_IN2 = 9;

const int BUZZER = 10;

const int LEFT_SERVO = 11;
const int RIGHT_SERVO = 12;

const int DFPLAYER_RX = A0;
const int DFPLAYER_TX = A1;

const int TRIG = A2;
const int ECHO = A3;

const int LED1 = A4;
const int LED2 = A5;

Servo leftHand;
Servo rightHand;

SoftwareSerial dfSerial(DFPLAYER_RX, DFPLAYER_TX);
DFRobotDFPlayerMini dfPlayer;

bool dfPlayerReady = false;

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  return duration / 58;
}

void motor1(int direction) {
  if (direction > 0) {
    digitalWrite(M1_IN1, HIGH);
    digitalWrite(M1_IN2, LOW);
  } else if (direction < 0) {
    digitalWrite(M1_IN1, LOW);
    digitalWrite(M1_IN2, HIGH);
  } else {
    digitalWrite(M1_IN1, LOW);
    digitalWrite(M1_IN2, LOW);
  }
}

void motor2(int direction) {
  if (direction > 0) {
    digitalWrite(M2_IN1, HIGH);
    digitalWrite(M2_IN2, LOW);
  } else if (direction < 0) {
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, HIGH);
  } else {
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, LOW);
  }
}

void motor3(int direction) {
  if (direction > 0) {
    digitalWrite(M3_IN1, HIGH);
    digitalWrite(M3_IN2, LOW);
  } else if (direction < 0) {
    digitalWrite(M3_IN1, LOW);
    digitalWrite(M3_IN2, HIGH);
  } else {
    digitalWrite(M3_IN1, LOW);
    digitalWrite(M3_IN2, LOW);
  }
}

void motor4(int direction) {
  if (direction > 0) {
    digitalWrite(M4_IN1, HIGH);
    digitalWrite(M4_IN2, LOW);
  } else if (direction < 0) {
    digitalWrite(M4_IN1, LOW);
    digitalWrite(M4_IN2, HIGH);
  } else {
    digitalWrite(M4_IN1, LOW);
    digitalWrite(M4_IN2, LOW);
  }
}

void stopMotors() {
  motor1(0);
  motor2(0);
  motor3(0);
  motor4(0);
}

void forward() {
  motor1(1);
  motor2(1);
  motor3(1);
  motor4(1);
}

void backward() {
  motor1(-1);
  motor2(-1);
  motor3(-1);
  motor4(-1);
}

void turnLeft() {
  motor1(-1);
  motor2(-1);
  motor3(1);
  motor4(1);
}

void turnRight() {
  motor1(1);
  motor2(1);
  motor3(-1);
  motor4(-1);
}

void waveHands() {
  for (int i = 0; i < 3; i++) {
    leftHand.write(55);
    rightHand.write(125);
    delay(250);

    leftHand.write(115);
    rightHand.write(65);
    delay(250);
  }

  leftHand.write(90);
  rightHand.write(90);
}

void greetingSound() {
  tone(BUZZER, 1000, 200);
  delay(250);

  tone(BUZZER, 1400, 200);
  delay(250);

  noTone(BUZZER);

  if (dfPlayerReady) {
    dfPlayer.play(1);
  }
}

void greeting() {
  stopMotors();

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);

  greetingSound();

  waveHands();

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void setup() {
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);

  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);

  pinMode(M3_IN1, OUTPUT);
  pinMode(M3_IN2, OUTPUT);

  pinMode(M4_IN1, OUTPUT);
  pinMode(M4_IN2, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  leftHand.attach(LEFT_SERVO);
  rightHand.attach(RIGHT_SERVO);

  leftHand.write(90);
  rightHand.write(90);

  stopMotors();

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  dfSerial.begin(9600);

  delay(1000);

  if (dfPlayer.begin(dfSerial)) {
    dfPlayerReady = true;
    dfPlayer.volume(25);
  }
}

void loop() {
  long distance = getDistance();

  if (distance <= 50) {
    greeting();
    delay(3000);
  } else {
    stopMotors();
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }

  delay(100);
}
