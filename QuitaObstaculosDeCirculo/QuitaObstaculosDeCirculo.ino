
#include <ArduinoSTL.h>

#define DEBUG(a) Serial.println(a);

//Constantes Motores
#define MAX_POWER_MOTOR 255
#define MIN_POWER_MOTOR 0

#define MOTOR_RIGHT_PWM      3
#define MOTOR_RIGHT_REARWARD 4
#define MOTOR_RIGHT_FORWARD   5

#define MOTOR_LEFT_PWM       9
#define MOTOR_LEFT_REARWARD  10
#define MOTOR_LEFT_FORWARD   11

//Constantes Tiempos
#define TIME_STOP
#define TIME_BACK
#define TIME_SPIN
#define TIME_RANDOM


#define DISTANCE_TRUE 5


int  state = 0,
   

long getDistance(int trigger, int echo) {
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long duracion = pulseIn(echo, HIGH);
  long distancia = (duracion / 2) / 29;
  return distancia;
}


bool enableForward(){
  return  ( (getDistance(FRONT_TRIG, FRONT_ECHO) > STOP_DISTANCE)
          &&(getDistance(LEFT_TRIG,  LEFT_ECHO ) > STOP_DISTANCE)
          &&(getDistance(RIGHT_TRIG, RIGHT_ECHO) > STOP_DISTANCE)
          );
   
}


bool enableRearward(){
  return (getDistance(BACK_TRIG, BACK_ECHO) > STOP_DISTANCE );
}


std::vector<void (*)()>  stateMachine = {
  // -----------------Estado 0 - STOP----------------------//
  []() { 
    if ( ){
    }
    
    speed = 0;
    digitalWrite(MOTOR_RIGHT_REARWARD,LOW);
    digitalWrite(MOTOR_LEFT_REARWARD, LOW);
    digitalWrite(MOTOR_LEFT_FORWARD , LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  },
  // ------------------Estado 1 - BACK----------------------//
  []() {  
    if (){ 
      state = 0;
      DEBUG("DETENIDO");
      DEBUG(speed);
    }
    speed = map(anglePitchPhone,HALF_PITCH - PITCH_OFFSET_NULL,MIN_PITCH,MIN_POWER_MOTOR,MAX_POWER_MOTOR);
    digitalWrite(MOTOR_RIGHT_REARWARD,LOW);
    digitalWrite(MOTOR_LEFT_REARWARD, HIGH);
    digitalWrite(MOTOR_LEFT_FORWARD , LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  },
  // ------------------Estado 2 - SPIN--------------------//
  []() { 
    if (){
      state = 0;
      DEBUG("DETENIDO");
      DEBUG(speed);
    } 
    speed = map(anglePitchPhone,HALF_PITCH + PITCH_OFFSET_NULL,MAX_PITCH,MIN_POWER_MOTOR,MAX_POWER_MOTOR);
    digitalWrite(MOTOR_RIGHT_REARWARD,HIGH);
    digitalWrite(MOTOR_LEFT_REARWARD, LOW);
    digitalWrite(MOTOR_LEFT_FORWARD , HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    
    
  },
  // ------------------Estado 3 - FORWARD-----------------------//
  []() { 
    if (){
      state = 0;
      DEBUG("DETENIDO");
      DEBUG(speed);
    } 
    speed = map(angleRollPhone,HALF_ROLL + ROLL_OFFSET_NULL,MAX_ROLL,MIN_POWER_MOTOR,MAX_POWER_MOTOR);
    digitalWrite(MOTOR_RIGHT_REARWARD,HIGH);
    digitalWrite(MOTOR_LEFT_REARWARD, HIGH);
    digitalWrite(MOTOR_LEFT_FORWARD , LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    
  }
};


void setup()
{
  Serial.begin(9600);
  ESP8266.begin(9600);
  
  pinMode(MOTOR_LEFT_PWM,     OUTPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_REARWARD,OUTPUT);

  pinMode(MOTOR_RIGHT_PWM,     OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_REARWARD,OUTPUT);

  digitalWrite(MOTOR_RIGHT_REARWARD,LOW);
  digitalWrite(MOTOR_LEFT_REARWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD , LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);

}
void loop() {
 
    
    stateMachine[state]();
    analogWrite(MOTOR_RIGHT_PWM, speed);
    analogWrite(MOTOR_LEFT_PWM,  speed);
}
  





