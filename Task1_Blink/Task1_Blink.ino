#define LED 5

int delayTime = 4000;  // start with a four second on / four second off blink

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 5 as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (delayTime < 1) {
    digitalWrite(LED, HIGH);  // frequency is now "infinite" -- stay on permanently
    return;
  }

  digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(delayTime);         // wait
  digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  delay(delayTime);         // wait

  delayTime = delayTime / 2;  // halve the delay so the blink frequency doubles
}
