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
    initialize();
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

    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);        //NON Inverted PWM
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10); //PRESCALER=64 MODE 14(FAST PWM)
    ICR1 = 2499;

    EIMSK |= (1 << INT4);   

    DDRC |=  (1 << PC5);    // Aux 3 -> Ramp Servo
    DDRC |=  (1 << PC6);    // Aux 4 -> Generic PWM

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
// 2250 - 2375
void DeployCore::update()
{
    
    Led::setStatusLed(1, true);
    Led::setStatusLed(2, false);

    m_servo.setAngle(0);
    m_controller.move(1000);

    _delay_ms(150);

    Led::setStatusLed(1, false);
    Led::setStatusLed(2, true);

    m_servo.setAngle(180);
    m_controller.move(-1000);

    _delay_ms(150);

    //for (int i = 0; i < 60; i++)
    //{
        _delay_ms(1000);
    //}
    
}