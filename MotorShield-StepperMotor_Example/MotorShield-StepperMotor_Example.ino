/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

- Stepper Motor Guide (https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-stepper-motors)
*/

#include <Adafruit_MotorShield.h>

/* Create Motor Shield */
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

/* Create Stepper Motor
 * Connect a stepper motor with 200 steps per revolution (1.8 degree)
 * to motor port #1 (M1 and M2) 
 */
Adafruit_StepperMotor *stepperMotor = AFMS.getStepper(200, 1);

/* POTENTIOMETER INPUTS */
#define STEPPER_POT_PIN A1 // Data pin from potentiometer connected to analog pin 1
int STEPPER_BasePotRead = 0;
int STEPPER_NewPotRead = 0;

void setup() {
  /* Serial Library Setup BEGIN */
  Serial.begin(9600);
  while (!Serial);
  /* Serial Library Setup END */

  /* Motor Shield Setup BEGIN */
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  /* Motor Shield Setup END */

  stepperMotor->setSpeed(50);  // 50 rpm
}

void loop() {
  STEPPER_NewPotRead = map(analogRead(STEPPER_POT_PIN),0,1023,0,500);
  if (STEPPER_NewPotRead > STEPPER_BasePotRead + 1) {
    stepperMotor->step(5, FORWARD, SINGLE);
  }
  if (STEPPER_NewPotRead < STEPPER_BasePotRead - 1) {
    stepperMotor->step(5, BACKWARD, SINGLE);
  }
  STEPPER_BasePotRead = STEPPER_NewPotRead;

  delay(1);
}