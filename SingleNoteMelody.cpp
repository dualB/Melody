#include "SingleNoteMelody.h"
#include "Arduino.h"
SingleNoteMelody::SingleNoteMelody(Note *note)
{

    _note = note;
    _hasNext = false;
}

SingleNoteMelody::~SingleNoteMelody()
{
    _note = nullptr;
}

bool SingleNoteMelody::hasNext()
{
    return _hasNext;
}
void SingleNoteMelody::restart()
{
    _hasNext = true;
}
void SingleNoteMelody::next()
{
    _hasNext = false;
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
int SingleNoteMelody::getIntensityIndex()
{
    return _note->getIntensityIndex();
}