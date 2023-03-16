/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

Contains examples for 3 kinds of motors:
- stepper motor (https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-stepper-motors)
- DC motor(https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-dc-motors)
- RC Servo (https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-rc-servos)
*/

#include <Adafruit_MotorShield.h>
#include <Servo.h>

/* Create Motor Shield */
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

/* Create Servo */
Servo servo_180;

/* Create Stepper Motor
 * Connect a stepper motor with 200 steps per revolution (1.8 degree)
 * to motor port #1 (M1 and M2) 
 */
Adafruit_StepperMotor *stepperMotor = AFMS.getStepper(200, 1);

/* Create DC TOY MOTOR
 * Select which 'port' M1, M2, M3 or M4. In this case, M3
 */
Adafruit_DCMotor *TOY_dcMotor = AFMS.getMotor(3);

/* Create DC TT MOTOR
 * Select which 'port' M1, M2, M3 or M4. In this case, M3
 */
Adafruit_DCMotor *TTGM_dcMotor = AFMS.getMotor(4);

/* POTENTIOMETER INPUTS */
#define SERVO_POT_PIN A0
int servoPotVal;
#define TOY_DC_POT_PIN A2
int TOY_BasePotRead;
int TOY_NewPotRead;
#define TTGM_DC_POT_PIN A3
int TTGM_BasePotRead;
int TTGM_NewPotRead;
#define STEPPER_POT_PIN A1
int STEPPER_BasePotRead;
int STEPPER_NewPotRead;

void setup() {
  /* Serial Library Setup BEGIN */
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Stepper test!");
  /* Serial Library Setup END */

  /* Pot BEGIN */
  TTGM_BasePotRead = analogRead(TTGM_DC_POT_PIN);
  TOY_BasePotRead = analogRead(TOY_DC_POT_PIN);
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


  stepperMotor->setSpeed(50);  // 10 rpm
  TTGM_dcMotor->setSpeed(50);
  TOY_dcMotor->setSpeed(50);
}

void loop() {
  servoPotVal = map(analogRead(SERVO_POT_PIN), 0, 1023, 0, 180);
  servo_180.write(servoPotVal);

  /* Stepper Motor Loop BEGIN */
  STEPPER_NewPotRead = map(analogRead(STEPPER_POT_PIN),0,1023,0,500);
  if (STEPPER_NewPotRead > STEPPER_BasePotRead + 1) {
    stepperMotor->step(5, FORWARD, SINGLE);
  }
  if (STEPPER_NewPotRead < STEPPER_BasePotRead - 1) {
    stepperMotor->step(5, BACKWARD, SINGLE);
  }
  STEPPER_BasePotRead = STEPPER_NewPotRead;
  /* Stepper Motor Loop END */

  TOY_NewPotRead = analogRead(TOY_DC_POT_PIN);
  // +- 1 to smooth out range
  if (TOY_NewPotRead > TOY_BasePotRead + 3) {
    TOY_dcMotor->run(FORWARD);
    TOY_BasePotRead = TOY_NewPotRead;
  } else if (TOY_NewPotRead < TOY_BasePotRead - 3) {
    TOY_dcMotor->run(BACKWARD);
    TOY_BasePotRead = TOY_NewPotRead;
  } else {
    TOY_dcMotor->run(RELEASE);
  }

  /* Rotary Encoder BEGIN */
    
  TTGM_NewPotRead = analogRead(TTGM_DC_POT_PIN);
  // +- 1 to smooth out range
  if (TTGM_NewPotRead > TTGM_BasePotRead + 3) {
    TTGM_dcMotor->run(BACKWARD);
    TTGM_BasePotRead = TTGM_NewPotRead;
  } else if (TTGM_NewPotRead < TTGM_BasePotRead - 3) {
    TTGM_dcMotor->run(FORWARD);
    TTGM_BasePotRead = TTGM_NewPotRead;
  } else {
    TTGM_dcMotor->run(RELEASE);
  }

  delay(1);
  /* Rotary Encoder END */
}