// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#ifndef DEPLOYCORE_HPP
#define DEPLOYCORE_HPP

#include <stdio.h>

#include "motorcontroller.hpp"
#include "servo.hpp"

namespace aviware
{
    namespace jA
    {
        class DeployCore
        {
        public:
            DeployCore(const int stepsPerPackage);

            ~DeployCore() = default;

            void initialize();

            void run();

        private:

            void update();

            void deploy();

            MotorController m_controller{};

            Servo m_servo{};

            const int8_t m_packageCount = 5;

            int8_t m_deployedCount = 0;

            const int m_stepsPerPackage;
        }; // class DeployCore
        
    } // namespace jA
    
} // namespace aviware


#endif // !DEPLOYCORE_HPP