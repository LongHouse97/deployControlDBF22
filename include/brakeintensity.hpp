// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 05 March 2022
//

#ifndef BRAKE_INTENSITY_HPP
#define BRAKE_INTENSITY_HPP

namespace aviware
{
    namespace jA
    {
        enum BrakeIntensity{
            NONE = 0,
            LOW,
            MEDIUM_LOW,
            MEDIUM,
            MEDIUM_HIGH,
            HIGH,
            MAX
        }; // enum BrakeIntensity

    } // namespace jA
    
} // namespace aviware


#endif // !BRAKE_INTENSITY_HPP