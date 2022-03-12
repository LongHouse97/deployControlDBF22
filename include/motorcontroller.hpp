// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 19 Feb 2022
//

#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

namespace aviware
{
    namespace jA
    {
        class MotorController
        {
        public:
            MotorController();

            ~MotorController() = default;

            static void move(const int steps);

            static void home();

        }; // class MotorController

    } // namespace jA
    
} // namespace aviware

#endif // !MOTOR_CONTROLLER_HPP