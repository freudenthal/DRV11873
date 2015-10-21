/*
DRV11873.cpp Library for controlling DRV11873 Brushless Motor Driver
Last update 9/4/2015
Sean Kirkpatrick
*/



#include "DRV11873.h"

// #define DEBUG

DRV11873::DRV11873()
//base constructor
{
	// InitializePins(15,22,23,9,10);
}

// void DRV11873::InitializePins(uint8_t _pinBlocked, uint8_t _pinFreq, uint8_t _pinHiLo, uint8_t _pinReverse, uint8_t _pinPWMSpeed)
// {
// 		uint8_t pinBlocked = _pinBlocked;
// 		uint8_t pinFreq = _pinFreq;
// 		uint8_t pinHiLo = _pinHiLo;
// 		uint8_t pinReverse = _pinReverse;
// 		uint8_t pinPWMSpeed = _pinPWMSpeed;
// 		pinMode(pinBlocked, INPUT);
// 		pinMode(pinFreq, INPUT);
// 		pinMode(pinHiLo, OUTPUT);
// 		pinMode(pinReverse, OUTPUT);
// 		pinMode(pinPWMSpeed, OUTPUT);
// }

DRV11873::~DRV11873()
//base destructor
{

}

void DRV11873::setSpeedMode(SpeedMode Mode)
{
	if(Mode == SpeedMode::High)
	{
		digitalWrite(pinHiLo, HIGH);
	}else{
		digitalWrite(pinHiLo, LOW);
	}
}

void DRV11873::setDirectionMode(DirectionMode Mode)
{
	if(Mode == DirectionMode::CounterClockwise)
	{
		digitalWrite(pinReverse, HIGH);	//counter-clockwise
	}else{
		digitalWrite(pinReverse, LOW);	//clockwise
	}
}

void DRV11873::setSpeedPercentage(float DutyCycle)
{
	CurrentDutyCycle = (uint8_t)DutyCycle*255/100;	//store target duty cycle
	setSpeed(CurrentDutyCycle);
}

void DRV11873::setSpeed(uint8_t DutyCycle)
//PWM control of motor with duty cycle ranging from 0-255
//DRV11873 requires PWM frequency beteween 7 to 100 kHz, so PWM clock must be adjusted
{
	if(CurrentDutyCycle > 0)
	{digitalWrite(pinPWMSpeed, HIGH);	//for testing purposes only
	}else{digitalWrite(pinPWMSpeed, LOW);}
	// analogWriteFrequency(pinPWMSpeed, 96000);  //set timer0 to 96kHz affects pins 5,6,9,10,20,21,22,23
	// analogWrite(pinPWMSpeed, DutyCycle);
}

float DRV11873::readFrequency()
// frequency generator is 50% duty cycle with variable frequency
{
	int SAMPLES = 100;
  	long freq = 0;
  	long t1;
  	// long t2;
  	long t = 0;
  for(int j=0; j<SAMPLES; j++) 
  {
	t1 = micros();
    freq = pulseIn(pinFreq, HIGH,1000000);
	#ifdef DEBUG
		Serial.print(freq);Serial.println(" us");
	#endif
    t += micros()-t1;  //elapsed time in microseconds
    }
  return (float)(SAMPLES*1000000/(float)t); // freq = 1/t/samples = samples/t
}