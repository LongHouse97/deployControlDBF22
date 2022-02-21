// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 19 Feb 2022
//

#include "motorcontroller.hpp"

using namespace aviware::jA;

MotorController::MotorController()
{
    
}

void MotorController::move(const int steps)
{
    m_currentPosition += steps;

    m_motor.move(steps);
}

void MotorController::home()
{
    m_motor.move(-m_currentPosition);

    resetSteps();
}

void MotorController::resetSteps() 
{
    m_currentPosition = 0;
}