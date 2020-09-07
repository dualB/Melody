#include "SingleNoteMelody.h"

SingleNoteMelody::SingleNoteMelody(Note *note)
{
    _played = false;
    _note = note;
}

SingleNoteMelody::~SingleNoteMelody()
{
    delete _note;
    _note = nullptr;
}

bool SingleNoteMelody::hasNext()
{
    return !_played;
}
void SingleNoteMelody::restart()
{
    _played = false;
}
Note *SingleNoteMelody::next()
{
    _played = true;
    return _note;
}