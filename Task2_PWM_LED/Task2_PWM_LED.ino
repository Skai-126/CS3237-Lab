#define LEDPIN 5
#define LEDCHANNEL 1
#define LEDFREQ 5000
#define LEDRESOLUTION 8

// PWM DutyCycle
int brightness = 0;
int fadeAmount = 5;  // how much to change the brightness each step

void setup() {
  ledcAttachChannel(LEDPIN, LEDFREQ, LEDRESOLUTION, LEDCHANNEL);
  ledcWriteChannel(LEDCHANNEL, brightness);
}

void loop() {
  ledcWriteChannel(LEDCHANNEL, brightness);

  brightness += fadeAmount;

  // reverse direction at the top and bottom of the range
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  delay(30);  // wait a bit between each brightness step
}
