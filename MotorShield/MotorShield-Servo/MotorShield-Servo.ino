/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

- RC Servo Guide (https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-rc-servos)
*/

#include <Adafruit_MotorShield.h>
#include <Servo.h>

/* Create Motor Shield */
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

/* Create Servo */
Servo servo_180;

/* POTENTIOMETER INPUTS */
#define SERVO_POT_PIN A0
int servoPotVal;

void setup() {
  /* Serial Library Setup BEGIN */
  Serial.begin(9600);
  while (!Serial);
  /* Serial Library Setup END */

  /* Pot BEGIN */
  STEPPER_BasePotRead = analogRead(STEPPER_POT_PIN);
  /* Pot END */

  /* Servo BEGIN */
  servo_180.attach(10); // Servo 1 on motorshield
  // .attach(9); // Servo 2 on motorshield
  /* Servo END */

  /* Motor Shield Setup BEGIN */
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  /* Motor Shield Setup END */
}

void loop() {
  servoPotVal = map(analogRead(SERVO_POT_PIN), 0, 1023, 0, 180);
  servo_180.write(servoPotVal);

  delay(1);
}