#include "SingleNoteSequence.h"
#include "Arduino.h"
SingleNoteSequence::SingleNoteSequence(Note *note)
{

    _note = note;
    _hasNext = false;
}

SingleNoteSequence::~SingleNoteSequence()
{
    _note = nullptr;
}

bool SingleNoteSequence::hasNext()
{
    return _hasNext;
}
void SingleNoteSequence::restart()
{
    _hasNext = true;
}
void SingleNoteSequence::next()
{
    _hasNext = false;
}
int SingleNoteSequence::length()
{
    return 1;
}
int SingleNoteSequence::getNoteIndex()
{
    return _note->getNoteIndex();
}
bool SingleNoteSequence::isRest()
{
    return _note->isRest();
}
unsigned int SingleNoteSequence::getDurationNumerator()
{
    return _note->getDurationNumerator();
}
unsigned int SingleNoteSequence::getDurationDenominator()
{
    return _note->getDurationDenominator();
}
int SingleNoteSequence::getIntensityIndex()
{
    return _note->getIntensityIndex();
}