// Motor Control Pins
const int motor1EnablePin = 6;  // PWM Speed Control for Motor 1
const int motor1APin = 7;      // Direction Control 1A for Motor 1
const int motor1BPin = 8;      // Direction Control 1B for Motor 1
const int motor2EnablePin = 9; // PWM Speed Control for Motor 2
const int motor2APin = 4;      // Direction Control 2A for Motor 2
const int motor2BPin = 2;      // Direction Control 2B for Motor 2

// Encoder Pins
const int encoder1Pin = 3; // Encoder 1 Input Pin
const int encoder2Pin = 5; // Encoder 2 Input Pin

// Encoder Variables
volatile int encoder1Count = 0; // Counter for Encoder 1
volatile int encoder2Count = 0; // Counter for Encoder 2

// Function to drive the robot forward
void driveRobotForward() {
  digitalWrite(motor1APin, HIGH);
  digitalWrite(motor1BPin, LOW);
  digitalWrite(motor2APin, HIGH);
  digitalWrite(motor2BPin, LOW);
}

// Function to drive the robot in reverse
void driveRobotReverse() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, HIGH);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, HIGH);
}

// Function to control the speed of the motors
void controlSpeed(int speed) {
  analogWrite(motor1EnablePin, speed);
  analogWrite(motor2EnablePin, speed);
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, LOW);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, LOW);
}

// Function to spin the robot left
void spinRobotLeft() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, HIGH);
  digitalWrite(motor2APin, HIGH);
  digitalWrite(motor2BPin, LOW);
}

// Function to spin the robot right
void spinRobotRight() {
  digitalWrite(motor1APin, HIGH);
  digitalWrite(motor1BPin, LOW);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, HIGH);
}

// Function to turn the robot left
void turnRobotLeft() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, HIGH);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, LOW);
}

// Function to turn the robot right
void turnRobotRight() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, LOW);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, HIGH);
}

// Interrupt service routine for Encoder 1
void encoder1ISR() {
  encoder1Count++;
}

// Interrupt service routine for Encoder 2
void encoder2ISR() {
  encoder2Count++;
}

// Process the received serial command
void processSerialCommand(char command) {
  switch (command) {
    case 'F':
      driveRobotForward();
      break;
    case 'R':
      driveRobotReverse();
      break;
    case 'S':
      stopRobot();
      break;
    case 'L':
      spinRobotLeft();
      break;
    case 'M':
      spinRobotRight();
      break;
    case 'A':
      turnRobotLeft();
      break;
    case 'D':
      turnRobotRight();
      break;
    case 'C':
      controlSpeed(128); // Set speed to 128
      break;
    case 'P':
      Serial.print("Encoder 1 Count: ");
      Serial.println(encoder1Count);
      Serial.print("Encoder 2 Count: ");
      Serial.println(encoder2Count);
      break;
  }
}

void setup() {
  // Initialize motor control pins as outputs
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor1APin, OUTPUT);
  pinMode(motor1BPin, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(motor2APin, OUTPUT);
  pinMode(motor2BPin, OUTPUT);

  // Initialize encoder input pins as inputs with pull-up resistors
  pinMode(encoder1Pin, INPUT_PULLUP);
  pinMode(encoder2Pin, INPUT_PULLUP);

  // Attach interrupt service routines to encoder input pins
  attachInterrupt(digitalPinToInterrupt(encoder1Pin), encoder1ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder2Pin), encoder2ISR, CHANGE);

  // Set initial speed and direction
  controlSpeed(255); // Max speed
  driveRobotForward();

  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Example usage: Drive forward for 2 seconds, then stop for 1 second
  driveRobotForward();
  delay(2000);
  stopRobot();
  delay(1000);

  // Check if there's any serial data available
  if (Serial.available()) {
    char command = Serial.read();
    processSerialCommand(command);
  }
}
