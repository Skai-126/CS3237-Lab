#define PIN 4
#define DEBOUNCE_DELAY 100  // ms, minimum time between accepted presses

volatile bool pressed = false;
volatile int pressCount = 0;
volatile unsigned long lastInterruptTime = 0;

void IRAM_ATTR isr() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > DEBOUNCE_DELAY) {
    pressCount++;
    pressed = true;
  }
  lastInterruptTime = interruptTime;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN, INPUT_PULLUP);
  attachInterrupt(PIN, isr, FALLING);
}

void loop() {
  if (pressed) {
    Serial.printf("Button has been pressed %u times\n", pressCount);
    pressed = false;
  }
}
