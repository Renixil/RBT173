// Motor Control Pins
const int motor1EnablePin = 6;  // PWM Speed Control for Motor 1
const int motor1APin = 7;      // Direction Control 1A for Motor 1
const int motor1BPin = 8;      // Direction Control 1B for Motor 1
const int motor2EnablePin = 9; // PWM Speed Control for Motor 2
const int motor2APin = 4;      // Direction Control 2A for Motor 2
const int motor2BPin = 2;      // Direction Control 2B for Motor 2

// Ultrasonic Sensor Pins
const int trigPin = 11;  // Trig pin of Ultrasonic Sensor
const int echoPin = 10;  // Echo pin of Ultrasonic Sensor

// Encoder Pins
const int encoder1Pin = 3; // Encoder 1 Input Pin
const int encoder2Pin = 5; // Encoder 2 Input Pin

// Encoder Variables
volatile int encoder1Count = 0; // Counter for Encoder 1
volatile int encoder2Count = 0; // Counter for Encoder 2

// Variables for speed control
const int maxSpeed = 255;     // Maximum speed value
const int minSpeed = 100;     // Minimum speed value
const int maxDistance = 50;   // Maximum distance for full stop
const int minDistance = 10;   // Minimum distance for maximum speed

// Variables for distance and rotation control
const float wheelDiameter = 65.0;       // Diameter of the wheels in mm
const float wheelCircumference = PI * wheelDiameter;  // Circumference of the wheels in mm
const float distancePerTick = wheelCircumference / 20;  // Distance traveled per encoder tick in mm
const int rotate90Ticks = 5;  // Number of encoder ticks to rotate 90 degrees

// Function to drive the robot forward with adjusted speed based on distance
void driveRobotForwardWithSpeed(int speed) {
  digitalWrite(motor1APin, HIGH);
  digitalWrite(motor1BPin, LOW);
  digitalWrite(motor2APin, HIGH);
  digitalWrite(motor2BPin, LOW);
  analogWrite(motor1EnablePin, speed);
  analogWrite(motor2EnablePin, speed);
}

// Function to drive the robot backward with adjusted speed
void driveRobotBackwardWithSpeed(int speed) {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, HIGH);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, HIGH);
  analogWrite(motor1EnablePin, speed);
  analogWrite(motor2EnablePin, speed);
}

// Function to turn the robot left in place
void turnRobotLeft() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, HIGH);
  digitalWrite(motor2APin, HIGH);
  digitalWrite(motor2BPin, LOW);
  analogWrite(motor1EnablePin, maxSpeed);
  analogWrite(motor2EnablePin, maxSpeed);
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, LOW);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, LOW);
}

// Function to read the distance from the Ultrasonic Sensor
int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Function to process the received serial command
void processSerialCommand(char command) {
  switch (command) {
    case 'F':
      driveRobotForwardWithSpeed(maxSpeed);
      break;
    case 'B':
      driveRobotBackwardWithSpeed(maxSpeed);
      break;
    case 'L':
      turnRobotLeft();
      break;
    case 'S':
      stopRobot();
      break;
    case 'P':
      Serial.print("Encoder 1 Count: ");
      Serial.println(encoder1Count);
      Serial.print("Encoder 2 Count: ");
      Serial.println(encoder2Count);
      break;
  }
}

// Interrupt service routine for Encoder 1
void encoder1ISR() {
  encoder1Count++;
}

// Interrupt service routine for Encoder 2
void encoder2ISR() {
  encoder2Count++;
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

  // Initialize Ultrasonic Sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set initial speed and direction
  driveRobotForwardWithSpeed(maxSpeed);

  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read distance from Ultrasonic Sensor
  int distance = readDistance();

  // Adjust speed based on distance
  int speed = map(distance, minDistance, maxDistance, minSpeed, maxSpeed);
  speed = constrain(speed, minSpeed, maxSpeed);

  // Drive the robot forward with adjusted speed
  driveRobotForwardWithSpeed(speed);

  // Check if an obstacle is detected
  if (distance <= minDistance) {
    // Stop the robot
    stopRobot();
    
    // Back up for a certain distance
    int backupDistance = 50; // Distance to back up in mm
    int backupTicks = backupDistance / distancePerTick;
    for (int i = 0; i < backupTicks; i++) {
      driveRobotBackwardWithSpeed(maxSpeed);
      delay(20);
    }
    
    // Turn the robot away from the obstacle
    int rotateTicks = rotate90Ticks; // Number of ticks to rotate 90 degrees
    for (int i = 0; i < rotateTicks; i++) {
      turnRobotLeft();
      delay(20);
    }
    
    // Resume driving forward
    driveRobotForwardWithSpeed(speed);
  }

  // Check if there's any serial data available
  if (Serial.available()) {
    char command = Serial.read();
    processSerialCommand(command);
  }
}
