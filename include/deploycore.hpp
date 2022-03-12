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

        private:

            void update();

        }; // class DeployCore
        
    } // namespace jA
    
} // namespace aviware


#endif // !DEPLOYCORE_HPP