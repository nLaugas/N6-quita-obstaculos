#include <DCMotor.h>
#include <Ping.h>

//constantes
#define TRIGGER    500
#define MAX_MOTOR_SPEED 100.0
#define MIN_MOTOR_SPEED  0.0
#define BLACK             


//sensors
#define RIGHT_IR A0
#define LEFT_IR  A1
#define ULTRASOUND A2


int leftSense = 1,rigthSense = 1;

DCMotor motorLeft(M0_EN, M0_D0, M0_D1);
DCMotor motorRight(M1_EN, M1_D0, M1_D1);
PingSensor ping(ULTRASOUND);


void setup()
{
  Serial.begin(9600);
  motorRight.setClockwise(false);
  motorRight.setSpeed(MIN_MOTOR_SPEED);
  motorLeft.setSpeed(MIN_MOTOR_SPEED);
}


void loop() {
  //state turn
  if (){
      
  }

  if (){

  }

  if (){

  }

  if (){

  }

  motorRight.setSpeed(MAN_MOTOR_SPEED*rigthSense);
    motorLeft.setSpeed(MAN_MOTOR_SPEED*leftSense);

}
