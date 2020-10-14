#include "ModifierRepetition.h"

ModifierRepetition::ModifierRepetition(unsigned int times, Sequence *note) : Modifier(note)
{
    _times = times;
    _count = 1;
}

bool ModifierRepetition::hasNext()
{
    return get()->hasNext() || _count < _times;
}
void ModifierRepetition::restart()
{
    _count = 1;
    get()->restart();
}
void ModifierRepetition::next()
{
    if (get()->hasNext())
    {
        get()->next();
    }
    else if (_count < _times)
    {
        get()->restart();
        get()->next();
        _count++;
    }
    else
    {
        //nothing to do
    }
}
int ModifierRepetition::length()
{
    return _times * get()->length();
}