// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 17 Feb 2022
//

#ifndef STEPPERMOTOR_HPP
#define STEPPERMOTOR_HPP

namespace aviware
{
    namespace jA
    {
        class StepperMotor
        {
        public:

            static void move(const int numberOfSteps);

        private:

            static void singleStep();

        }; // class StepperMotor
        
    } // namespace jA
    
} // namespace aviware

#endif // !STEPPERMOTOR_HPP