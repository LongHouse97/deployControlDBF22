// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#ifndef STATUSLEDS_HPP
#define STATUSLEDS_HPP

#include <avr/io.h>
#include "helpers.hpp"

#define LED1 PORTD, 5
#define LED2 PORTD, 6

enum LedState{ NONE, ONE, TWO, BOTH };

namespace aviware
{
    namespace jA
    {
        class Led
        {
            public:
            
            static void setStatusLed(const uint8_t led, const bool state);

            static int getOffset();
        }; // class Led
        
    } // namespace jA
    
} // namespace aviware


#endif // !STATUSLEDS_HPP