#define SWITCH 4
byte state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SWITCH) == LOW) {
    state = !state;
    delay(300);  // debounce delay: wait for the switch contacts to settle before reading again
  }

  if (state) {
    Serial.println("Toggle On");
  } else {
    Serial.println("Toggle Off");
  }
}
