#define TRIGPIN 12
#define ECHOPIN 14
#define LEDPIN 5

#define MIN_DISTANCE 2     // cm, closest distance we care about
#define MAX_DISTANCE 100   // cm, farthest distance we care about
#define MIN_BLINK_INTERVAL 50    // ms, fastest blink (when close)
#define MAX_BLINK_INTERVAL 2000  // ms, slowest blink (when far)

unsigned long lastToggleTime = 0;
bool ledState = LOW;
unsigned long blinkInterval = MAX_BLINK_INTERVAL;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  // send a 10us pulse on TRIG to trigger a measurement
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  // measure how long ECHO stays HIGH, convert to distance in cm (with a 30ms timeout)
  long duration = pulseIn(ECHOPIN, HIGH, 30000);
  float distanceCm = duration * 0.0343 / 2;

  if (distanceCm > 0) {
    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");

    // closer object -> smaller blinkInterval -> faster blinking
    float clamped = constrain(distanceCm, MIN_DISTANCE, MAX_DISTANCE);
    float ratio = (clamped - MIN_DISTANCE) / (float)(MAX_DISTANCE - MIN_DISTANCE);
    blinkInterval = MIN_BLINK_INTERVAL + ratio * (MAX_BLINK_INTERVAL - MIN_BLINK_INTERVAL);
  }

  // non-blocking blink: toggle the LED once blinkInterval/2 has passed
  unsigned long now = millis();
  if (now - lastToggleTime >= blinkInterval / 2) {
    ledState = !ledState;
    digitalWrite(LEDPIN, ledState);
    lastToggleTime = now;
  }
}