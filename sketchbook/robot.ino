/*
 * Original sourse: https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 * This is the Arduino code PAC6985 16 channel servo controller
 * watch the video for details and demo http://youtu.be/y8X9X10Tn1k
 *  * 
 * Written by Ahmad Nejrabi for Robojax Video channel www.Robojax.com
 * Date: Dec 16, 2017, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * this code has been downloaded from http://robojax.com/learn/arduino/
 * 
 */
/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t ROTATION_SERVO = 4; //pin set 3 was acting funny I think
uint8_t HAND_SERVO = 2;
uint8_t UP_AND_DOWN_SERVO = 1;
uint8_t FRONT_AND_BACK_SERVO = 0;

int angleToPulse(int ang ){
   const int servoMin = 0;
   const int servoMax = 180;
   int pulse = map(ang, servoMin, servoMax, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  //yield();
}

int currRotation = 90;
int newRotation = 90;
int currUpAndDown = 90;
int newUpAndDown = 90;
int currFrontAndBack = 90;
int newFrontAndBack = 90;
int currHand = 90;
int newHand = 90;


const int minRot = 1;
const int maxRot = 179;

const int minUpDn = 10;
const int maxUpDn = 80;

const int minFtBk = 10;
const int maxFtBk = 50;

const int minHand = 1;
const int maxHand = 179;

void loop() {
  if(Serial.available() > 0)
  {
    char incoming = Serial.read();
    switch(incoming)
    {
        case( '0' ):
        {
            newRotation = max(minRot,currRotation - 2);
            pwm.setPWM(ROTATION_SERVO, 0, angleToPulse( newRotation ));    
            currRotation = newRotation;
            break;
        }   
        case( '1' ):
        {        
            newRotation = min(maxRot, currRotation + 2);
            pwm.setPWM(ROTATION_SERVO, 0, angleToPulse( newRotation ));    
            currRotation = newRotation;
            break;
        }
        case( '2' ):
        {
            newUpAndDown = max(minUpDn,currUpAndDown - 2);
            pwm.setPWM(UP_AND_DOWN_SERVO, 0, angleToPulse( newUpAndDown ));    
            currUpAndDown = newUpAndDown;
            break;
        }    
        case( '3' ):
        {
            newUpAndDown = min(maxUpDn, currUpAndDown + 2);
            pwm.setPWM(UP_AND_DOWN_SERVO, 0, angleToPulse( newUpAndDown ));    
            currUpAndDown = newUpAndDown;
            break;
        }
        case( '4' ):
        {    
            newFrontAndBack = max(minFtBk,currFrontAndBack - 2);
            pwm.setPWM(FRONT_AND_BACK_SERVO, 0, angleToPulse( newFrontAndBack ));    
            currFrontAndBack = newFrontAndBack;
            break;
        }
        case( '5' ):
        {
            newFrontAndBack = min(maxFtBk, currFrontAndBack + 2);
            pwm.setPWM(FRONT_AND_BACK_SERVO, 0, angleToPulse( newFrontAndBack ));    
            currFrontAndBack = newFrontAndBack;
            break;
        }

        case( '6' ):
        {
            newHand = max( minHand, currHand - 2);
            pwm.setPWM(HAND_SERVO, 0, angleToPulse( newHand ));    
            currHand = newHand;
            break;
        }
        case( '7' ):
        {
            newHand = min(maxHand, currHand + 2);
            pwm.setPWM(HAND_SERVO, 0, angleToPulse( newHand ));    
            currHand = newHand;
            break;
        }
    }
  }
}
