// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 20 Feb 2022
//

#include "statusleds.hpp"

using namespace aviware::jA;

static LedState ledState = NONE;

static constexpr int ledOffset[4] = { 0, 32, 64, 96 };

int Led::getOffset()
{
    return ledOffset[ledState];
}

void Led::setStatusLed(const uint8_t led, const bool state)
{
    switch (led)
    {
    case 1:
        if (state)
        {
            C_SETBIT(LED1);
        
            switch (ledState)
            {
            case NONE:
                ledState = ONE;
                break;
            case ONE:
                break;
            case TWO:
                ledState = BOTH;
            case BOTH:
                break;
            }
            
        }else
        {
            C_CLEARBIT(LED1);

            switch (ledState)
            {
            case NONE:
                break;
            case ONE:
                ledState = NONE;
                break;
            case TWO:
                break;
            case BOTH:
                ledState = TWO;
                break;
            }
        }
        break;
    case 2:

        if(state)
        {
            C_SETBIT(LED2);

            switch (ledState)
            {
            case NONE:
                ledState = TWO;
                break;
            case ONE:
                ledState = BOTH;
                break;
            case TWO:
                break;
            case BOTH:
                break;
            }
        }else
        {
            C_CLEARBIT(LED2);

            switch (ledState)
            {
            case NONE:
                break;
            case ONE:
                break;
            case TWO:
                ledState = NONE;
                break;
            case BOTH:
                ledState = ONE;
                break;
            }
        }
        break;
    }
}