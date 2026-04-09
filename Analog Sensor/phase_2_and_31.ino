int photoresistorPin = A0;
int ledPin = 2;
int minSensorValue = 0;    // Minimum value from the photoresistor
int maxSensorValue = 1023; // Maximum value from the photoresistor

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(photoresistorPin);
  int mappedValue = map(sensorValue, minSensorValue, maxSensorValue, 0, 255);
  analogWrite(ledPin, mappedValue);
  Serial.println(mappedValue);
  delay(100);
}