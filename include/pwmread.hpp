// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 18 Feb 2022
//

#ifndef PWM_READ_HPP
#define PWM_READ_HPP

#include <avr/io.h>

namespace aviware
{
    namespace jA
    {
        class PwmRead
        {
        public:
            PwmRead() = default;

            ~PwmRead() = default;

            static bool isDeployTriggered();

            static bool isBrakeTriggered();

            static void resetDeployFlag();

            static void resetBrakeFlag();

            static int getBrakeIntensity();
            
        }; // class PwmRead
    } // namespace jA
    
} // namespace aviware

#endif // !PWM_READ_HPP