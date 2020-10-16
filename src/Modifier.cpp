#include "Modifier.h"

Modifier::Modifier(Sequence * Sequence)
{
    set(Sequence);
}

void Modifier::set(Sequence *base)
{
    _base = base;
}

Sequence *Modifier::get()
{
    return _base;
}
