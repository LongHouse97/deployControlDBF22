// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 21 Feb 2022
//

#ifndef SERVO_HPP
#define SERVO_HPP

namespace aviware
{
    namespace jA
    {
        class Servo
        {
        public:
            static void open();

            static void close();
        }; // class Servo

    } // namespace jA
    
} // namespace aviware


#endif // !SERVO_HPP