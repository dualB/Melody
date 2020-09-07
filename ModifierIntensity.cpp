#include "ModifierIntensity.h"

ModifierIntensity::ModifierIntensity( int deltaIntensity)
{

    _deltaIntensity = deltaIntensity;
}

int ModifierIntensity::getIntensity() { return _deltaIntensity + getBase()->getIntensity(); }