#include <DCMotor.h>
#include <Ping.h>


#define MAX_MOTOR_SPEED      100.0
#define MIN_MOTOR_SPEED      0.0
#define BLACK_LINE        500 
#define DINSTANCE_TO_OBJECT     10

#define RIGHT_IR        A0
#define LEFT_IR         A1
#define ULTRASOUND        A2

#define TIME_STOP 4000
#define TIME_BACK 4000
#define TIME_SPIN 4000


int leftSense  = 1;
int rigthSense = 1;
int state = 2;
long currentTime, lastTime = 0;

DCMotor leftMotor(M0_EN, M0_D0, M0_D1);
DCMotor rightMotor(M1_EN, M1_D0, M1_D1);
PingSensor ping(ULTRASOUND);


void setup()
{
  Serial.begin(9600);
  rightMotor.setClockwise(false);
  rightMotor.setSpeed(MIN_MOTOR_SPEED);
  leftMotor.setSpeed(MIN_MOTOR_SPEED);
}


void loop() {
  
  currentTime = millis(); 

  switch (state)
  {
    case 1: //--------STOP--------------------------------------------------------------------
           if ((currentTime - lastTime ) > TIME_STOP)
           {
              state = 3; //BACK
              rigthSense = -1;
              leftSense  = -1;
              lastTime = currentTime;
              Serial.println("BACK");
           }
               break;

    case 2: //-------FORWARD------------------------------------------------------------------
           if ((analogRead(RIGHT_IR) > BLACK_LINE) || (analogRead(LEFT_IR) > BLACK_LINE)) 
           {
              state = 1; //STOP
              rigthSense = 0;
              leftSense  = 0;
              lastTime = currentTime;
              Serial.println("STOP");
           }
               break;
    case 3: //-------BACK---------------------------------------------------------------------
          if ((currentTime - lastTime ) > TIME_BACK)
          {
              state = 4; //SPIN 
              rigthSense =  1;
              leftSense  = -1;
              lastTime = currentTime;
              Serial.println("SPIN");
            }
                break;

    case 4: //-------SPIN----------------------------------------------------------------------
          if (((currentTime - lastTime ) > TIME_SPIN) || (ping.measureCM() < DINSTANCE_TO_OBJECT))
          {
              state = 2; //FORWARD
              rigthSense = 1;
              leftSense  = 1;
              lastTime = currentTime;
              Serial.println("FORWARD");
            }
                break;
    }

    
    rightMotor.setSpeed(MAX_MOTOR_SPEED*(-rigthSense));
    leftMotor.setSpeed(MAX_MOTOR_SPEED*leftSense);


}


