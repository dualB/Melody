#include "SingleNoteMelody.h"
#include "Arduino.h"
SingleNoteMelody::SingleNoteMelody(Note *note)
{

    _note = note;
}

SingleNoteMelody::~SingleNoteMelody()
{
    _note = nullptr;
}

bool SingleNoteMelody::hasNext()
{
    return false;
}
void SingleNoteMelody::restart()
{
}
void SingleNoteMelody::next()
{
}
int SingleNoteMelody::length()
{
    return 1;
}
int SingleNoteMelody::getNoteIndex()
{
    return _note->getNoteIndex();
}
bool SingleNoteMelody::isRest()
{
    return _note->isRest();
}
unsigned int SingleNoteMelody::getDurationNumerator()
{
    return _note->getDurationNumerator();
}
unsigned int SingleNoteMelody::getDurationDenominator()
{
    return _note->getDurationDenominator();
}
int SingleNoteMelody::getIntensity()
{
    return _note->getIntensity();
}