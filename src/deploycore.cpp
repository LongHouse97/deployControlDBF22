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
#include "pwmread.hpp"
#include "statusleds.hpp"

using namespace aviware::jA;

DeployCore::DeployCore(const int stepsPerPackage) :
    m_stepsPerPackage(stepsPerPackage)
{
    initialize();
}

void DeployCore::initialize()
{
    /*
        DDRx &= ~(1 << Pxn); -> Eingang
        DDRx |= (1 << Pxn);  -> Ausgang
    */

    DDRC |=  (1 << DDC5);    // Aux 3 -> Ramp Servo
    DDRC |=  (1 << DDC6);    // Aux 4 -> Generic PWM

    DDRD |=  (1 << DDD0);    // Motor Pin 1
    DDRD |=  (1 << DDD1);    // Motor Pin 2
    DDRD |=  (1 << DDD2);    // Motor Pin 3
    DDRD |=  (1 << DDD3);    // Motor Pin 4
    DDRD |=  (1 << DDD5);    // LED 1
    DDRD |=  (1 << DDD6);    // LED 2

    TCCR0B |= (1 << CS02);  // Prescaler 256 for Timer 0B

    PORTC |= (1 << PC7);    // Activate pullupressistor of PC7
    EIMSK |= (1 << INT4);   
    EICRB |= (1 << ISC40);
    EICRB |= (1 << ISC41);  // <- Toggle 1 Raising Edge 0 Falling Edge

    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);        //NON Inverted PWM
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10); //PRESCALER=64 MODE 14(FAST PWM)
    ICR1 = 2499;

    EIMSK |= (1 << INT4);

    Led::setStatusLed(1, true);
    Led::setStatusLed(2, true);

    m_servo.setAngle(180);
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
    if(PwmRead::isBrakeTriggered())
    {
        // TODO Control Brakes
        Led::setStatusLed(1, false);
    }else
    {
        Led::setStatusLed(1, true);
        PwmRead::resetBrakeFlag();
    }
    if (PwmRead::isDeployTriggered())
    {
        // Start Deploy Sequence
        deploy();
        _delay_ms(25);
        PwmRead::resetDeployFlag();
    }
        
    sei();
}

void DeployCore::deploy()
{   
    if (m_deployedCount < m_packageCount)
    {
        Led::setStatusLed(2, false);
        m_deployedCount++;
        m_servo.setAngle(0); // Open Close?
        m_controller.move(-m_stepsPerPackage * m_deployedCount);
        m_controller.home();
        m_servo.setAngle(180);
    }else
    {
        for (size_t i = 0; i < 8; i++)
        {
            Led::setStatusLed(2, false);
            _delay_ms(250);
            Led::setStatusLed(2, true);
            _delay_ms(250);
        }
    }
    Led::setStatusLed(2, true);
}