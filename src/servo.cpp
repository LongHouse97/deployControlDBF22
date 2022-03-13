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

static constexpr int lowerLimit = 195; // default 75

static constexpr int upperLimit = 267; // default 300

volatile float currentAngle = lowerLimit;

void Servo::open()
{
    OCR1B = lowerLimit;
}

void Servo::close()
{
    OCR1B = upperLimit;
}