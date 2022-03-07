// 
// (C) aviware 2022
// Author: Arian Ghoddousi, BSc
// Contact: arian.ghoddousi@aviware.net 
// Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
// Date: 05 March 2022
//

#include <avr/io.h>

#include "brakes.hpp"

using namespace aviware::jA;

static constexpr int lowerLimit = 0;

static constexpr int upperLimit = 2498;

//volatile float brakeAction = lowerLimit;

static const int brakeAction[] = {0, 250, 500, 1000, 1500, 2000, 2498};

void Brakes::setBrakeIntensity(const int intensity)
{
    //brakeAction = (intensity / 100) * (upperLimit - lowerLimit) + lowerLimit;

    OCR1A = brakeAction[intensity];
    //OCR1A = 0;
}