//Digital Pins positions

#define segmentPin_A 6
#define segmentPin_B 7
#define segmentPin_C 8
#define segmentPin_D 9
#define segmentPin_E 10
#define segmentPin_F 11
#define segmentPin_G 12

#define ButtonPin_1 5
#define ButtonPin_2 4
#define ButtonPin_4 3
#define ButtonPin_8 2

void setup() {
  pinMode(ButtonPin_1, INPUT);
  pinMode(ButtonPin_2, INPUT);
  pinMode(ButtonPin_4, INPUT);
  pinMode(ButtonPin_8, INPUT);
  
  pinMode(segmentPin_A, OUTPUT);
  pinMode(segmentPin_B, OUTPUT);
  pinMode(segmentPin_C, OUTPUT);
  pinMode(segmentPin_D, OUTPUT);
  pinMode(segmentPin_E, OUTPUT);
  pinMode(segmentPin_F, OUTPUT);
  pinMode(segmentPin_G, OUTPUT);
}

void displayDigit(int digit) {
  // Clear all segments
  digitalWrite(segmentPin_A, HIGH);
  digitalWrite(segmentPin_B, HIGH);
  digitalWrite(segmentPin_C, HIGH);
  digitalWrite(segmentPin_D, HIGH);
  digitalWrite(segmentPin_E, HIGH);
  digitalWrite(segmentPin_F, HIGH);
  digitalWrite(segmentPin_G, HIGH);
  
  // Display the appropriate segments based on the digit
  switch (digit) {
    case 0:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_C, LOW);
      digitalWrite(segmentPin_D, LOW);
      digitalWrite(segmentPin_E, LOW);
      digitalWrite(segmentPin_F, LOW);
      break;
    case 1:
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_C, LOW);
      break;
    case 2:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_D, LOW);
      digitalWrite(segmentPin_E, LOW);
      digitalWrite(segmentPin_G, LOW);
      break;
    case 3:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_C, LOW);
      digitalWrite(segmentPin_D, LOW);
      digitalWrite(segmentPin_G, LOW);
      break;
    case 4:
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_C, LOW);
      digitalWrite(segmentPin_F, LOW);
      digitalWrite(segmentPin_G, LOW);
      break;
    case 5:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_C, LOW);
      digitalWrite(segmentPin_D, LOW);
      digitalWrite(segmentPin_F, LOW);
      digitalWrite(segmentPin_G, LOW);
      break;
    case 6:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_C, LOW);
      digitalWrite(segmentPin_D, LOW);
      digitalWrite(segmentPin_E, LOW);
      digitalWrite(segmentPin_F, LOW);
      digitalWrite(segmentPin_G, LOW);
      break;
    case 7:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_C, LOW);
      break;
    case 8:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_C, LOW);
      digitalWrite(segmentPin_D, LOW);
      digitalWrite(segmentPin_E, LOW);
      digitalWrite(segmentPin_F, LOW);
      digitalWrite(segmentPin_G, LOW);
      break;
    case 9:
      digitalWrite(segmentPin_A, LOW);
      digitalWrite(segmentPin_B, LOW);
      digitalWrite(segmentPin_C, LOW);
      digitalWrite(segmentPin_D, LOW);
      digitalWrite(segmentPin_F, LOW);
      digitalWrite(segmentPin_G, LOW);
      break;
    
  }
}

void loop() {
  bool w = !digitalRead(ButtonPin_1);
  bool x = !digitalRead(ButtonPin_2);
  bool y = !digitalRead(ButtonPin_4);
  bool z = !digitalRead(ButtonPin_8);

  digitalWrite(segmentPin_A, (!x && !z) || (!w && y) || (!w && x && z) || (x && z) || (w && !x && !y));
  digitalWrite(segmentPin_B, (!w && !y && !z) || (!x && !y) || (!x && !z) || (w && y && z) || (w && !y && z));
  digitalWrite(segmentPin_C, (!x && !y) || (!x && z) || (!y && z) || (!w && x) || (w && !x));
  digitalWrite(segmentPin_D, (!x && !y && !z) || (!w && y && !z) || (!x && y && z) || (x && !y && z) || (w && x && !z));
  digitalWrite(segmentPin_E, (!x && !z) || (y && !z) || (w && y) || (w && x));
  digitalWrite(segmentPin_F, (!x && !y && !z) || (!w && x && !y) || (x && y && !z) || (w && !x) || (w && y));
  digitalWrite(segmentPin_G, (!x && y) || (x && !z) || w || (w && x && !y && z));
}
