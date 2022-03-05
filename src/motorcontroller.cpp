// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 19 Feb 2022
//

#include "motorcontroller.hpp"
#include "steppermotor.hpp"

using namespace aviware::jA;

static int currentPosition = 0;

MotorController::MotorController()
{
    
}

void MotorController::move(const int steps)
{
    currentPosition += steps;

    StepperMotor::move(steps);
}

void MotorController::home()
{
    StepperMotor::move(-currentPosition);

    resetSteps();
}

void MotorController::resetSteps() 
{
    currentPosition = 0;
}