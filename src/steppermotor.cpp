// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "helpers.hpp"
#include "statusleds.hpp"
#include "steppermotor.hpp"

using namespace aviware::jA;

static constexpr int stepsPerRevolution = 200;

static volatile int currentStep = 0;

static constexpr long long stepDelay = 90000000UL / ( stepsPerRevolution * 360UL );

void StepperMotor::move(const int numberOfSteps)
{
    int remainingSteps = abs(numberOfSteps);

    int8_t direction = 0;

    numberOfSteps > 0 ? direction = 1 : direction = -1;
    
    while (remainingSteps > 0)
    {
        switch (direction)
        {
        case 1:
            currentStep++;
            if(currentStep == stepsPerRevolution)
            {
                currentStep = 0;
            }
            break;
        case -1:
            if(currentStep == 0)
            {
                currentStep = stepsPerRevolution;
            }
            currentStep--;
            break;
        }
        remainingSteps--;
        singleStep();
        _delay_us(stepDelay);
    }
}

void StepperMotor::singleStep()
{
    switch (currentStep % 4)
    {
    case 0:
        PORTD = 5 + Led::getOffset();
        break;
    case 1:
        PORTD = 6 + Led::getOffset();
        break;
    case 2:
        PORTD = 10 + Led::getOffset();
        break;
    case 3:
        PORTD = 9 + Led::getOffset();
        break;
    }
}
