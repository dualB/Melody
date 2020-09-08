#include "ModifierIntensity.h"

ModifierIntensity::ModifierIntensity( int deltaIntensity,Melody *note): Modifier(note)
{

    _deltaIntensity = deltaIntensity;
}

int ModifierIntensity::getIntensity() { return _deltaIntensity + get()->getIntensity(); }