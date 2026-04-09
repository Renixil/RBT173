// C++ code
int timer =100; // Global Variable for timer 100 milliseconds.

void setup() {

  for (int DataPin = 2; DataPin < 6; DataPin++) {
    pinMode(DataPin, OUTPUT);

  }
}

void loop() {

  for (int DataPin = 2; DataPin < 6; DataPin++) {
    digitalWrite(DataPin, HIGH);
    delay(timer);
    digitalWrite(DataPin, LOW);
  }
  for (int DataPin = 6; DataPin >= 2; DataPin--) {
    digitalWrite(DataPin, HIGH);
    delay(timer);
    digitalWrite(DataPin, LOW);

  }
}
