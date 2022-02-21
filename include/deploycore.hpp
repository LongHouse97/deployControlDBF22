// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#ifndef DEPLOYCORE_HPP
#define DEPLOYCORE_HPP

#include "motorcontroller.hpp"
#include "servo.hpp"

namespace aviware
{
    namespace jA
    {
        class DeployCore
        {
        public:
            DeployCore();

            ~DeployCore() = default;

            void initialize();

            void run();

            void update();

        private:

            MotorController m_controller{};

            Servo m_servo{};
        }; // class DeployCore
        
    } // namespace jA
    
} // namespace aviware


#endif // !DEPLOYCORE_HPP