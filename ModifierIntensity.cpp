#include "ModifierIntensity.h"

ModifierIntensity::ModifierIntensity( int deltaIntensity,Melody *note): Modifier(note)
{

    _deltaIntensity = deltaIntensity;
}

int ModifierIntensity::getIntensityIndex() { return _deltaIntensity + get()->getIntensityIndex(); }