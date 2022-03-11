// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 05 March 2022
//

#ifndef BRAKES_HPP
#define BRAKES_HPP

#include "brakeintensity.hpp"

namespace aviware
{
    namespace jA
    {
        class Brakes
        {
        public:
            static void setBrakeIntensity(const BrakeIntensity intensity);

            static void activate();

            static void release();

        }; // class Brakes;
        
    } // namespace jA
    
} // namespace aviware


#endif // !BRAKES_HPP