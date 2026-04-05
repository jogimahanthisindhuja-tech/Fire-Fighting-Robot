#include <Servo.h>
#include <SoftwareSerial.h>

// Motor Pins
const int motor1Pin1 = 8;
const int motor1Pin2 = 9;
const int motor2Pin1 = 10;
const int motor2Pin2 = 11;

// Flame Sensors
const int flameLeft = A0;
const int flameCenter = A1;
const int flameRight = A2;

// Servo & Pump
const int servoPin = 6;
const int pumpPin = 7;

// Threshold
const int flameThreshold = 500;

// Objects
Servo servo;
SoftwareSerial BT(2, 3); // RX, TX

// Mode Control
bool manualModeEnabled = false;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(pumpPin, OUTPUT);

  servo.attach(servoPin);
  servo.write(90); // Center position

  digitalWrite(pumpPin, LOW);

  BT.begin(9600);
  Serial.begin(9600);

  Serial.println(" Fire Fighting Robot Ready");
  Serial.println("Send 'M' for Manual Mode, 'A' for Auto Mode");
}

void loop() {
  // Read flame sensors
  int left = analogRead(flameLeft);
  int center = analogRead(flameCenter);
  int right = analogRead(flameRight);

  // Debug values
  Serial.print("L: "); Serial.print(left);
  Serial.print(" C: "); Serial.print(center);
  Serial.print(" R: "); Serial.println(right);

  // Check Bluetooth commands
  if (BT.available()) {
    char command = BT.read();
    Serial.print("Command: "); Serial.println(command);

    if (command == 'M') {
      manualModeEnabled = true;
      stopMotors();
      Serial.println("Manual Mode Enabled");
    } 
    else if (command == 'A') {
      manualModeEnabled = false;
      stopMotors();
      Serial.println("Auto Mode Enabled");
    } 
    else if (manualModeEnabled) {
      manualControl(command);
    }
  }

  // Automatic Mode
  if (!manualModeEnabled) {
    if (left < flameThreshold || center < flameThreshold || right < flameThreshold) {
      automaticMode(left, center, right);
    } else {
      stopMotors();
      digitalWrite(pumpPin, LOW);
    }
  }
}

//  AUTOMATIC MODE
void automaticMode(int left, int center, int right) {
  if (center < flameThreshold) {
    Serial.println("Fire Ahead");
    forward();
    delay(400);
    stopMotors();
    sprayWater();
  } 
  else if (left < flameThreshold) {
    Serial.println("Fire Left");
    leftTurn();
    delay(400);
    forward();
    delay(400);
    stopMotors();
    sprayWater();
  } 
  else if (right < flameThreshold) {
    Serial.println("Fire Right");
    rightTurn();
    delay(400);
    forward();
    delay(400);
    stopMotors();
    sprayWater();
  }
}

//  MANUAL CONTROL
void manualControl(char command) {
  if (command == 'F') forward();
  else if (command == 'B') backward();
  else if (command == 'L') leftTurn();
  else if (command == 'R') rightTurn();
  else if (command == 'S') stopMotors();
}

//  MOVEMENT FUNCTIONS
void forward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void backward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void leftTurn() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void rightTurn() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

//  SPRAY WATER FUNCTION
void sprayWater() {
  Serial.println(" Spraying Water...");

  digitalWrite(pumpPin, HIGH);

  // Servo sweep
  for (int pos = 60; pos <= 120; pos += 5) {
    servo.write(pos);
    delay(40);
  }
  for (int pos = 120; pos >= 60; pos -= 5) {
    servo.write(pos);
    delay(40);
  }

  digitalWrite(pumpPin, LOW);
  delay(500);
}
