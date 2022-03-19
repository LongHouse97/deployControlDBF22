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

#include "brakes.hpp"
#include "brakeintensity.hpp"
#include "deploycore.hpp"
#include "motorcontroller.hpp"
#include "servo.hpp"
#include "statusleds.hpp"

#define TIMER2US(x) (x * 8) 

using namespace aviware::jA;

static volatile uint8_t dT;

static const int8_t packageCount = 5;

static int8_t deployedCount = 0;

static int stepsPerPackage = 500;

void deploy();

DeployCore::DeployCore()
{
    initialize();
}

ISR(INT4_vect)
{
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

    if (TIMER2US(dT) >= 1472 && TIMER2US(dT) <= 2016)
    {
        //Brakes::activate();
        PORTC |= (1 << PC4);
        Led::setStatusLed(1, false);
    }else
    {
        //Brakes::release();
        PORTC &= ~(1 << PC4);
        Led::setStatusLed(1, true);
    }
    if (TIMER2US(dT) >= 920 && TIMER2US(dT) <= 1080) // old Value 1248
    {
        cli();
        dT = 0;
        //deploy();
        if (deployedCount < packageCount)
        {
            Led::setStatusLed(2, false);
            deployedCount++;
            Servo::open();
            MotorController::move(-stepsPerPackage * deployedCount);
            MotorController::home();
            _delay_ms(500);
            Servo::close();
            _delay_ms(1000);
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
        SETBIT(EIFR, INTF4);
        sei();
    }
}

void DeployCore::initialize()
{
    /*
        DDRx &= ~(1 << Pxn); -> Eingang
        DDRx |= (1 << Pxn);  -> Ausgang
    */

    DDRC |=  (1 << DDC4);    // Aux 2 -> Brake Signal
    DDRC |=  (1 << DDC5);    // Aux 3 -> Ramp Servo

    DDRD |=  (1 << DDD0);    // Motor Pin 1
    DDRD |=  (1 << DDD1);    // Motor Pin 2
    DDRD |=  (1 << DDD2);    // Motor Pin 3
    DDRD |=  (1 << DDD3);    // Motor Pin 4
    DDRD |=  (1 << DDD5);    // LED 1
    DDRD |=  (1 << DDD6);    // LED 2

    TCCR0B |= (1 << CS00);  // Prescaler 64 for Timer 0B
    TCCR0B |= (1 << CS01);

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

    Servo::close();

    _delay_ms(500);

    MotorController::move(1);
    _delay_ms(50);
    MotorController::home();

    sei();
}

void DeployCore::run()
{
    while (true)
    {

    }   
}

void deploy()
{   
    cli();
    if (deployedCount < packageCount)
    {
        Led::setStatusLed(2, false);
        deployedCount++;
        Servo::open();
        MotorController::move(-stepsPerPackage * deployedCount);
        MotorController::home();
        _delay_ms(500);
        Servo::close();
        _delay_ms(2000);
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
    _delay_ms(2000);
    sei();
}
