/*
DRV11873.h Library for controlling DRV11873 Brushless Motor Driver
Last update 9/4/2015
Sean Kirkpatrick

Comms are through direct pin I/O, not over I2C
*/

#ifndef DRV11873_h	//check for multiple inclusions
#define DRV11873_h

//pin assignments 
#define pinBlocked 15
#define pinFreq 22
#define pinHiLo 23
#define pinReverse 9
#define pinPWMSpeed 10

#include "Arduino.h"

enum class SpeedMode{High, Low};
enum class DirectionMode{Clockwise, CounterClockwise};
enum class ControlMode{Manual, Automatic};

class DRV11873
{
	public:
		//constructors
		DRV11873();
		~DRV11873();
		//methods
		void setSpeedMode(SpeedMode Mode);
		void setDirectionMode(DirectionMode Mode);
		void setSpeedPercentage(float Duty);
		float readFrequency();
	private:
		//private functions
		void setSpeed(uint8_t DutyCycle);
		uint8_t CurrentDutyCycle;
		// void InitializePins(uint8_t _pinBlocked, uint8_t _pinFreq, uint8_t _pinHiLo, uint8_t _pinReverse, uint8_t _pinPWMSpeed);
		// void setPwmFrequency(int pin, int divisor);
};

#endif