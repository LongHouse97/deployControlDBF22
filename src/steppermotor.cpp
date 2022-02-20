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

static constexpr long long stepDelay = 60000000UL / ( stepsPerRevolution * 360UL );


void setPin(const uint8_t pin, const bool state)
{
    switch (pin)
    {
        case 1:
            state ? PORTD |= (1 << PD0) : PORTD &= ~(1 << PD0);
            break;
        case 2:
            state ? PORTD |= (1 << PD1) : PORTD &= ~(1 << PD1);
            break;
        case 3:
            state ? PORTD |= (1 << PD2) : PORTD &= ~(1 << PD2);
            break;
        case 4:
            state ? PORTD |= (1 << PD3) : PORTD &= ~(1 << PD3);
            break;
    }
}

StepperMotor::StepperMotor()
{

}

StepperMotor::~StepperMotor()
{

}

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
        //PORTD = 0x05;
        PORTD = 5 + Led::getOffset();
        //SETBITMASK(PORTD, 0x05);
        break;
    case 1:
        //PORTD = 0x06;
        PORTD = 6 + Led::getOffset();
        //SETBITMASK(PORTD, 0x06);
        break;
    case 2:
        //PORTD = 0x0A;
        PORTD = 10 + Led::getOffset();
        //SETBITMASK(PORTD, 0x0A);
        break;
    case 3:
        //PORTD = 0x09;
        PORTD = 9 + Led::getOffset();
        //SETBITMASK(PORTD, 0x09);
        break;
    }
}

//setPin(1, true);
        //setPin(2, false);
        //setPin(3, true);
        //setPin(4, false);

//setPin(1, false);
        //setPin(2, true);
        //setPin(3, true);
        //setPin(4, false);

//setPin(1, false);
        //setPin(2, true);
        //setPin(3, false);
        //setPin(4, true);

//setPin(1, true);
        //setPin(2, false);
        //setPin(3, false);
        //setPin(4, true);