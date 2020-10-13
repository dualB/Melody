#include "EmptyMelody.h"

EmptyMelody::EmptyMelody()
{
}

EmptyMelody::~EmptyMelody()
{
}

bool EmptyMelody::hasNext()
{
    return false;
}
void EmptyMelody::restart()
{
}
void EmptyMelody::next()
{
}

int EmptyMelody::length()
{
    return 0;
}

int EmptyMelody::getNoteIndex()
{
    return 0;
}
bool EmptyMelody::isRest()
{
    return true;
}
unsigned int EmptyMelody::getDurationNumerator()
{
    return 1;
}
unsigned int EmptyMelody::getDurationDenominator()
{
    return 1;
}
int EmptyMelody::getIntensityIndex()
{
    return 0;
}