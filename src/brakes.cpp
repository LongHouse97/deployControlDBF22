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

static constexpr int lowerLimit = 50;

static constexpr int upperLimit = 2500;

volatile float brakeAction = lowerLimit;

void Brakes::setBrakeIntensity(const int intensity)
{
    brakeAction = (intensity / 100) * (upperLimit - lowerLimit);

    OCR1A = (int)brakeAction;
}