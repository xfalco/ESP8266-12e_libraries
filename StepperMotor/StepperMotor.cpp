#include "StepperMotor.h"

StepperMotor::StepperMotor(uint8_t ms1, uint8_t ms2, uint8_t dir, uint8_t step)
:_ms1(ms1),
_ms2(ms2),
_dir(dir),
_step(step)
{}

void StepperMotor::setup() {
  pinMode(_ms1, OUTPUT);
  pinMode(_ms2, OUTPUT);
  pinMode(_dir, OUTPUT);
  pinMode(_step, OUTPUT);
}

void StepperMotor::rotate(int numSteps) {
	rotate(numSteps, LOW);
}

void StepperMotor::rotate(int numSteps, int direction) {
	rotate(numSteps, direction, MEDIUM);
}

void StepperMotor::rotate(int numSteps, int direction, String speed) {
	rotate(numSteps, direction, speed, EIGTH_STEP);
}

void StepperMotor::rotate(int numSteps, int direction, String speed, String stepType) {
	int _delay = 16;
	digitalWrite(_dir, direction);
	if(stepType.equals(FULL_STEP)) {
		digitalWrite(_ms1, LOW);
		digitalWrite(_ms2, LOW);
	} else if(stepType.equals(HALF_STEP)) {
		_delay /= 2;
		numSteps *= 2;
		digitalWrite(_ms1, HIGH);
		digitalWrite(_ms2, LOW);
	} else if(stepType.equals(QUARTER_STEP)) {
		_delay /= 4;
		numSteps *= 4;
		digitalWrite(_ms1, LOW);
		digitalWrite(_ms2, HIGH);
	} else {
		_delay /= 8;
		numSteps *= 8;
		digitalWrite(_ms1, HIGH);
		digitalWrite(_ms2, HIGH);
	}

	if(speed.equals(VERY_FAST)) {
		_delay /= 2;
	} else if(speed.equals(MEDIUM)) {
		_delay *= 2;
	} else if(speed.equals(SLOW)) {
		_delay *= 4;
	} else if(speed.equals(VERY_SLOW)) {
		_delay *= 8;
	}

	for (int idx = 0; idx < numSteps; idx++) {
		digitalWrite(_step, LOW);
		delay(_delay);
		digitalWrite(_step, HIGH);
		delay(_delay);
	}
}


StepperMotor::~StepperMotor() {}