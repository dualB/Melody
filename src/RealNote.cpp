#include "RealNote.h"

RealNote::RealNote(int index, bool rest)
{
    _index = index;
    _rest = rest;
}
int RealNote::getNoteIndex() { return _index; }
bool RealNote::isRest() { return _rest; }