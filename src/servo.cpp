// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 21 Feb 2022
//

#include <avr/io.h>

#include "servo.hpp"

using namespace aviware::jA;

static constexpr int lowerLimit = 75;

static constexpr int upperLimit = 300;

volatile float currentAngle = lowerLimit;

void Servo::setAngle(int angle)
{
    if (angle > 180)
    {
        angle = 180;
    }else if (angle < 0)
    {
        angle = 0;
    }
    
    currentAngle = (angle / 180) * (upperLimit - lowerLimit) + lowerLimit;

    OCR1B = (int)currentAngle;
}