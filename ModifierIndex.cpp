#include "ModifierIndex.h"

ModifierIndex::ModifierIndex(int deltaIndex,Melody *note): Modifier(note)
{
    _deltaIndex = deltaIndex;
}

int ModifierIndex::getNoteIndex() { return _deltaIndex + get()->getNoteIndex(); }
