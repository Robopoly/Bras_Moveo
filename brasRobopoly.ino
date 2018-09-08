// this code is only compatible with a boad based on the atmega 2560 e.g. arduino mega2560
#define dirPin 2,3,12,13,4    // pins to change steppers' directtion
#define tailleChaine 6        // string to communicate with the pi
#define pulPin 10,11,5,6,9    // pwm pins to move the steppers
#define nbStepper 5
#define maxServo 200          // max angle 
#define minServo 50           // min angle
#define pinServo 8

#include <Servo.h>

Servo servo;
int angle = 100;

const int pinStepper[nbStepper] = {pulPin};     
const int pinDirStepper[nbStepper] = {dirPin};  

char octetReception=0;
char chaineReception[tailleChaine]="000000";  // string to communicate with the pi

int i = 0;

void move_arm(){    // analyses the string and move the steppers 
  
  switch(chaineReception[0]-48){
    case 0:
      TCCR2A = TCCR2A & ~_BV(COM2A1) ;    // disable pwm
      break;
    case 1:
      digitalWrite(pinDirStepper[0],0) ;  // direction of the stepper
      TCCR2A = TCCR2A | _BV(COM2A1) ;     // enable pwm
      break;
    case 2:
      digitalWrite(pinDirStepper[0],1) ;  // direction of the stepper
      TCCR2A = TCCR2A | _BV(COM2A1) ;     // enable pwm
      break;
  }
  
  switch(chaineReception[1]-48){
    case 0:
      TCCR1A = TCCR1A & ~_BV(COM1A1) ;    // disable pwm
      break;
    case 1:
      digitalWrite(pinDirStepper[1],0) ;  // direction of the stepper
      TCCR1A = TCCR1A | _BV(COM1A1) ;     // enable pwm
      break;
    case 2:
      digitalWrite(pinDirStepper[1],1) ;  // direction of the stepper
      TCCR1A = TCCR1A | _BV(COM1A1) ;     // enable pwm
      break;
  } 
     
  switch(chaineReception[2]-48){
    case 0:
      TCCR3A = TCCR3A & ~_BV(COM3A1) ;    // disable pwm
      break;
    case 1:
      digitalWrite(pinDirStepper[2],0) ;  // direction of the stepper
      TCCR3A = TCCR3A | _BV(COM3A1) ;     // enable pwm
      break;
    case 2:
      digitalWrite(pinDirStepper[2],1) ;  // direction of the stepper
      TCCR3A = TCCR3A | _BV(COM3A1) ;     // enable pwm
      break;
  }
  
  switch(chaineReception[3]-48){
    case 0:
      TCCR4A = TCCR4A & ~_BV(COM4A1) ;    // disable pwm
      break;
    case 1:
      digitalWrite(pinDirStepper[3],0) ;  // direction of the stepper
      TCCR4A = TCCR4A | _BV(COM4A1) ;     // enable pwm
      break;
    case 2:
      digitalWrite(pinDirStepper[3],1) ;  // direction of the stepper
      TCCR4A = TCCR4A | _BV(COM4A1) ;     // enable pwm
      break;
  }
    switch(chaineReception[4]-48){
    case 0:
      TCCR2A = TCCR2A & ~_BV(COM2B1) ;    // disable pwm
      break;
    case 1:
      digitalWrite(pinDirStepper[4],0) ;  // direction of the stepper
      TCCR2A = TCCR2A | _BV(COM2B1) ;     // enable pwm
      break;
    case 2:
      digitalWrite(pinDirStepper[4],1) ;  // direction of the stepper
      TCCR2A = TCCR2A | _BV(COM2B1) ;     // enable pwm
      break;
  }

    switch(chaineReception[5]-48){           // this is the Servo
    case 2:
       angle = (angle < minServo) ? minServo : (angle > maxServo) ? maxServo : angle;
      for( int i = 0; i<5; i++){    // gradually decreases the angle
        servo.write(--angle);
      }
      break;
    case 1:
      angle = (angle < minServo) ? minServo : (angle > maxServo) ? maxServo : angle;
      for( int i = 0; i<5; i++){    // gradually increases the angle
        servo.write(++angle);
      }
      break;
  }
  
}
void setup() {
  

  // initialize Serial:
  Serial.begin(115200);
  
  // initialize pins
  for(int i = 0; i<nbStepper; i++){
    pinMode(pinStepper[i], OUTPUT);
    pinMode(pinDirStepper[i], OUTPUT);
    digitalWrite(pinStepper[i], LOW);
    digitalWrite(pinDirStepper[i], LOW);
  } 
    servo.attach(pinServo); 
    servo.write(angle);
    
   // initialize timers (1,2,3,4) on pwm_phase_corrected 8_bit (timer2 is already 8bit)
   // it's possible to use less timers using output B from timers ( if more timers are needed for another purpose)
   TCCR2A = _BV(WGM20);
   TCCR2B = _BV(CS22); // prescaler = 64 frequ = 490 Hz

   TCCR1A = _BV(WGM10);
   TCCR3A = _BV(WGM30);
   TCCR4A = _BV(WGM40);
   TCCR1B = _BV(CS10)|_BV(CS11);  // prescaler = 64 frequ = 490 Hz
   TCCR3B = _BV(CS20)|_BV(CS21);  // prescaler = 64 frequ = 490 Hz
   TCCR4B = _BV(CS30)|_BV(CS31);  // prescaler = 64 frequ = 490 Hz   
   
   // duty cycle = 50%
   OCR1A = 128; // pin 11
   OCR2A = 128; // pin 10
   OCR3A = 128; // pin 5
   OCR4A = 128; // pin 6
   OCR2B = 128; // pin 9
}



void loop() {         // here we read the string and call the function move_arm()
  while (Serial.available()>0) { 
          octetReception=Serial.read(); 
  
          if (octetReception==10) { // if == \n

                  move_arm();
                  i=0; 
                  break; 
          }
          else{
            chaineReception[i]= char(octetReception); // add the char readen to the string
            i++;
          }
  }
}
  
