// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "deploycore.hpp"
#include "motorcontroller.hpp"
#include "statusleds.hpp"

using namespace aviware::jA;

DeployCore::DeployCore()
{

}

void DeployCore::initialize()
{
    /*
        DDRx &= ~(1 << Pxn); -> Eingang
        DDRx |= (1 << Pxn);  -> Ausgang
    */

    //TCCR1B |= (1 << CS11); // /8 prescaler
    //TIFR = (1 << ICF1);    // clear interrupt-flag
    //TIMSK |= (1 << ICIE1); // enable Timer1 input capture interrupt

    // PORT C
    //DDRC |=  (1 << PC2);    // Aux 1 -> Ramp Servo
    //DDRC &=  (1 << PC4);    // PWM In (DeployTrigger)
    //DDRC &=  (1 << PC5);    // PWM In (WheelBreaks)

    // PORT D
    //DDRD = 0x6F;

    DDRD |=  (1 << PD0);    // Motor Pin 1
    DDRD |=  (1 << PD1);    // Motor Pin 2
    DDRD |=  (1 << PD2);    // Motor Pin 3
    DDRD |=  (1 << PD3);    // Motor Pin 4
    DDRD |=  (1 << PD5);    // LED 1
    DDRD |=  (1 << PD6);    // LED 2
}

void DeployCore::run()
{
    while (true)
    {
        update();
    }   
}

void DeployCore::update()
{
    Led::setStatusLed(1, true);
    Led::setStatusLed(2, false);
    m_controller.move(4000);
    _delay_ms(250);
    Led::setStatusLed(1, false);
    Led::setStatusLed(2, true);
    m_controller.move(-4000);
    _delay_ms(250);
}