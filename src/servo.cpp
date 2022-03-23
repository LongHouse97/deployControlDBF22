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

#define HORNET
//#define PROTOTYPE

#ifdef PROTOTYPE
    static constexpr int closePosition = 195; // default 75
    static constexpr int openPosition = 267; // default 300
#endif // PROTOTYPE

#ifdef HORNET
    static constexpr int closePosition = 260; // default 75
    static constexpr int openPosition = 130; // default 300
#endif // HORNET


void Servo::open()
{
    OCR1B = closePosition;
}

void Servo::close()
{
    OCR1B = openPosition;
}