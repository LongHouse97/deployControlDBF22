// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#include <avr/interrupt.h>

#include "pwmread.hpp"

#define TIMER2US(x) (x * 32) 

using namespace aviware::jA;

static volatile uint8_t dT;

static volatile bool deploy = false;

static volatile bool brake = false;



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
        //TODO: Map Break Intensity
        brake = true;
    }else
    {
        deploy = false;
        brake = false;
    }
}