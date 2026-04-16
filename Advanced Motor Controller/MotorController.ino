volatile int motor1EncoderCount = 0;
volatile int motor2EncoderCount = 0;
void setup() {
// Set pin modes for encoder inputs and enable internal pull-up resistors
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
// Attach interrupts to the encoder pins
attachInterrupt(digitalPinToInterrupt(2), motor1EncoderISR, RISING);
attachInterrupt(digitalPinToInterrupt(3), motor2EncoderISR, RISING);
// Initialize the serial communication
Serial.begin(9600);
}
void loop() {
// Perform other tasks here
// Print the encoder counts every second
static unsigned long previousTime = 0;
unsigned long currentTime = millis();
if (currentTime - previousTime >= 1000) {
previousTime = currentTime;
Serial.print("Motor 1 Encoder Count: ");
Serial.println(motor1EncoderCount);
Serial.print("Motor 2 Encoder Count: ");
Serial.println(motor2EncoderCount);
}
}
void motor1EncoderISR() {
// Check the state of phase-A to determine the direction
if (digitalRead(2) == HIGH) {
motor1EncoderCount++;
} else {
motor1EncoderCount--;
}
}
void motor2EncoderISR() {
// Check the state of phase-A to determine the direction
if (digitalRead(3) == HIGH) {
motor2EncoderCount++;
} else {
motor2EncoderCount--;
}
}
