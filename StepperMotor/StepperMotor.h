#ifndef StepperMotor_h
#define StepperMotor_h

#include "Arduino.h"
#include "stdint.h"

static String VERY_FAST  = "very_fast";
static String FAST       = "fast";
static String MEDIUM     = "medium";
static String SLOW       = "slow";
static String VERY_SLOW  = "very_slow";

static String FULL_STEP     = "full_step";
static String HALF_STEP     = "half_step";
static String QUARTER_STEP  = "quarter_step";
static String EIGTH_STEP    = "eigth_step";

class StepperMotor
{
  public:
  	StepperMotor(uint8_t ms1, uint8_t ms2, uint8_t dir, uint8_t step);
    ~StepperMotor();
    void setup();
    void rotate(int numSteps);
    void rotate(int numSteps, int direction);
    void rotate(int numSteps, int direction, String speed);
    void rotate(int numSteps, int direction, String speed, String stepType);
  private:
  	uint8_t _ms1;
    uint8_t _ms2;
    uint8_t _dir;
    uint8_t _step;
};

#endif