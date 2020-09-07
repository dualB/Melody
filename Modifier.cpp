#include "Modifier.h"

Modifier::Modifier()
{
}

void Modifier::setBase(Note *base)
{
    _base = base;
}

Note *Modifier::getBase()
{
    return _base;
}
