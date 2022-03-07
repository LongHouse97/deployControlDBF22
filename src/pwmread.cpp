// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#include <avr/interrupt.h>

#include "brakeintensity.hpp"
#include "pwmread.hpp"

#define TIMER2US(x) (x * 32) 

using namespace aviware::jA;

static volatile uint8_t dT;

static volatile bool deploy = false;

static volatile bool brake = false;

static volatile BrakeIntensity brakeIntensity = BrakeIntensity::NONE;

bool PwmRead::isDeployTriggered()
{
    return deploy;
}

bool PwmRead::isBrakeTriggered()
{
    return brake;
}

void PwmRead::resetDeployFlag()
{
    deploy = false;
}

void PwmRead::resetBrakeFlag()
{
    brake = false;
}

ISR(INT4_vect)
{
    cli();
    if (EICRB & (1 << ISC41)) 
    {
        TCNT0 = 0;
        // falling edge next
        EICRB &= ~(1<<ISC41);
    } else 
    {
        // rising edge next
        EICRB |= (1 << ISC41);
        dT = TCNT0;
    }

    if (TIMER2US(dT) >= 896 && TIMER2US(dT) <= 1248)
    {
        deploy = true;
    }else if (TIMER2US(dT) >= 1472 && TIMER2US(dT) <= 2016)
    {
        brake = true;
        /*
        brakeIntensity = (370 - 100 / 544 * TIMER2US(dT));

        if (brakeIntensity <= 0)
        {  
            brakeIntensity = 0;
        }else if (brakeIntensity >= 100)
        {
            brakeIntensity = 100;
        }*/
        
        if (TIMER2US(dT) >= 1472 && TIMER2US(dT) < 1505)
        {
            brakeIntensity = BrakeIntensity::MAX;
        }else if (TIMER2US(dT) >= 1505 && TIMER2US(dT) < 1600)
        {
            brakeIntensity = BrakeIntensity::HIGH;
        }else if (TIMER2US(dT) >= 1600 && TIMER2US(dT) < 1700)
        {
            brakeIntensity = BrakeIntensity::MEDIUM_HIGH;
        }else if (TIMER2US(dT) >= 1700 && TIMER2US(dT) < 1800)
        {
            brakeIntensity = BrakeIntensity::MEDIUM;
        }else if (TIMER2US(dT) >= 1800 && TIMER2US(dT) < 1900)
        {
            brakeIntensity = BrakeIntensity::MEDIUM_LOW;
        }else if (TIMER2US(dT) >= 1900 && TIMER2US(dT) < 2000)
        {
            brakeIntensity = BrakeIntensity::LOW;
        }else if (TIMER2US(dT) >= 2000)
        {
            brakeIntensity = BrakeIntensity::NONE;
        }
        

    }else
    {
        deploy = false;
        brake = false;
        brakeIntensity = BrakeIntensity::NONE;
    }
}

int PwmRead::getBrakeIntensity()
{
    return brakeIntensity;
}