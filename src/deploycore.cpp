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

#include "brakeintensity.hpp"
#include "deploycore.hpp"
#include "motorcontroller.hpp"
#include "servo.hpp"
#include "statusleds.hpp"

#define TIMER2US(x) (x * 8) 

#define BRAKE PORTC, PC4

using namespace aviware::jA;

static volatile uint8_t dT;
static volatile int8_t deployedCount = 0;
static constexpr int8_t packageCount = 5;
static constexpr int stepsPerPackage = 500;

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
        dT = 0;                 // Reset dT
        // falling edge next
        CLEARBIT(EICRB, ISC41);
    }else 
    {
        // rising edge next
        SETBIT(EICRB, ISC41);
        dT = TCNT0;
    }

    if (TIMER2US(dT) >= 1472 && TIMER2US(dT) <= 1560)
    {   // Activate Brakes
        C_SETBIT(BRAKE);
        Led::setStatusLed(1, false);
    }else
    {   // Release Brakes
        C_CLEARBIT(BRAKE);
        Led::setStatusLed(1, true);
    }
    if (TIMER2US(dT) >= 1040 && TIMER2US(dT) <= 1120)
    {
        cli();
        //deploy();
        SETBIT(EIFR, INTF4);    // Clear Pending Interrupt
        sei();
    }
}

void DeployCore::initialize()
{
    /*
        DDRx &= ~(1 << Pxn); -> Eingang
        DDRx |= (1 << Pxn);  -> Ausgang
    */


    SETBIT(DDRC, DDC4);     // Aux 2 -> Brake Signal
    SETBIT(DDRC, DDC5);     // Aux 3 -> Ramp Servo

    SETBIT(DDRD, DDD0);    // Motor Pin 1
    SETBIT(DDRD, DDD1);    // Motor Pin 2
    SETBIT(DDRD, DDD2);    // Motor Pin 3
    SETBIT(DDRD, DDD3);    // Motor Pin 4
    SETBIT(DDRD, DDD5);    // LED 1
    SETBIT(DDRD, DDD6);    // LED 2

    SETBIT(TCCR0B, CS00);   // Prescaler 64 for Timer 0B
    SETBIT(TCCR0B, CS01);

    SETBIT(PORTC, PC7);     // Activate pullupressistor of PC7
    SETBIT(EIMSK, INT4);
    SETBIT(EICRB, ISC40);
    SETBIT(EICRB, ISC41);   // <- Toggle 1 Raising Edge 0 Falling Edge

    SETBIT(TCCR1A, COM1A1); // NON Inverted PWM
    SETBIT(TCCR1A, COM1B1); // NON Inverted PWM
    SETBIT(TCCR1A, WGM11);  // NON Inverted PWM
    SETBIT(TCCR1B, WGM13);  // MODE 14(FAST PWM)
    SETBIT(TCCR1B, WGM12);  // MODE 14(FAST PWM)
    SETBIT(TCCR1B, CS10);   // PRESCALER=64 
    SETBIT(TCCR1B, CS11);   // PRESCALER=64

    ICR1 = 2499;

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
}