#include "EmptySequence.h"

EmptySequence::EmptySequence()
{
}

EmptySequence::~EmptySequence()
{
}

bool EmptySequence::hasNext()
{
    return false;
}
void EmptySequence::restart()
{
}
void EmptySequence::next()
{
    
}

int EmptySequence::length()
{
    return 0;
}

int EmptySequence::getNoteIndex()
{
    return 0;
}
bool EmptySequence::isRest()
{
    return true;
}
unsigned int EmptySequence::getDurationNumerator()
{
    return 1;
}
unsigned int EmptySequence::getDurationDenominator()
{
    return 1;
}
int EmptySequence::getIntensityIndex()
{
    return 0;
}