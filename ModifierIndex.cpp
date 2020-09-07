#include "ModifierIndex.h"

ModifierIndex::ModifierIndex(int deltaIndex)
{
    _deltaIndex = deltaIndex;
}

int ModifierIndex::getNoteIndex() { return _deltaIndex + getBase()->getNoteIndex(); }
