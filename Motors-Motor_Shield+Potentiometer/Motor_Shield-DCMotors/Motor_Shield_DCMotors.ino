/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

- DC motor Guide (https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-dc-motors)
*/

#include <Adafruit_MotorShield.h>

/* Create Motor Shield */
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

/* Create DC TOY MOTOR
 * Select which 'port' M1, M2, M3 or M4. In this case, M3
 */
Adafruit_DCMotor *TOY_dcMotor = AFMS.getMotor(3);

/* Create DC TT MOTOR
 * Select which 'port' M1, M2, M3 or M4. In this case, M4
 */
Adafruit_DCMotor *TTGM_dcMotor = AFMS.getMotor(4);

/* POTENTIOMETER INPUTS */
#define TOY_DC_POT_PIN A2 // Data pin from potentiometer connected to analog pin 2
int TOY_BasePotRead;
int TOY_NewPotRead;
#define TTGM_DC_POT_PIN A3 // Data pin from potentiometer connected to analog pin 3
int TTGM_BasePotRead;
int TTGM_NewPotRead;

void setup() {
  /* Serial Library Setup BEGIN */
  Serial.begin(9600);
  while (!Serial);
  /* Serial Library Setup END */

  /* Pot BEGIN */
  TTGM_BasePotRead = analogRead(TTGM_DC_POT_PIN);
  TOY_BasePotRead = analogRead(TOY_DC_POT_PIN);
  /* Pot END */

  /* Motor Shield Setup BEGIN */
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  /* Motor Shield Setup END */

  TTGM_dcMotor->setSpeed(50);
  TOY_dcMotor->setSpeed(50);
}

void loop() {
  TOY_NewPotRead = analogRead(TOY_DC_POT_PIN);
  // +- 3 to smooth out range
  if (TOY_NewPotRead > TOY_BasePotRead + 3) {
    TOY_dcMotor->run(FORWARD);
  } else if (TOY_NewPotRead < TOY_BasePotRead - 3) {
    TOY_dcMotor->run(BACKWARD);
  } else {
    TOY_dcMotor->run(RELEASE);
  }
  TOY_BasePotRead = TOY_NewPotRead;
    
  TTGM_NewPotRead = analogRead(TTGM_DC_POT_PIN);
  // +- 3 to smooth out range
  if (TTGM_NewPotRead > TTGM_BasePotRead + 3) {
    TTGM_dcMotor->run(BACKWARD);
  } else if (TTGM_NewPotRead < TTGM_BasePotRead - 3) {
    TTGM_dcMotor->run(FORWARD);
  } else {
    TTGM_dcMotor->run(RELEASE);
  }
  TTGM_BasePotRead = TTGM_NewPotRead;

  delay(1);
}