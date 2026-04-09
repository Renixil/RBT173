const int ledPins[] = {2, 3, 4, 5}; // LED Configuration
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const int trigPin = 9;  // Digital pin connected to the Trig pin of the ultrasonic sensor
const int echoPin = 10;  // Digital pin connected to the Echo pin of the ultrasonic sensor
const int potentiometerPin = A0; // Analog Pin
const int minDistance = 10;  // Minimum distance for LED movement
const int maxDistance = 100;  // Maximum distance for LED movement
const int brightnessThreshold = 10; // 

int currentLED = 0;  // Current LED index
int direction = 1;  // Direction of movement (1 = forward, -1 = backward)
int timer = 100;  // Global variable for timer in milliseconds

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int potentiometerValue = analogRead(potentiometerPin);
  int brightness = map(potentiometerValue, 0, 1023, 0, 255);

  // Larson Scanner movement
  analogWrite(ledPins[currentLED], brightness); // Control the brightness of the current LED

  Serial.println(potentiometerValue);

  if (brightness <= brightnessThreshold) {
    analogWrite(ledPins[currentLED], 0); // Turn off the current LED if brightness is below the threshold
  } else {
    analogWrite(ledPins[currentLED], 255); // Turn on the current LED at full brightness
  }

  delay(timer);

  analogWrite(ledPins[currentLED], 0); // Turn off the current LED

  currentLED += direction;

  // Reverse the direction if the end of the scanner is reached
  if (currentLED >= numLeds || currentLED < 0) {
    direction *= -1;
    currentLED += 2 * direction;
  }

  // Distance measurement for LED movement speed
  int distance = measureDistance();
  timer = map(distance, minDistance, maxDistance, 200, 50);

  delay(timer);
}

int measureDistance() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;

  // Limit the distance within the defined range
  distance = constrain(distance, minDistance, maxDistance);

  return distance;
}
