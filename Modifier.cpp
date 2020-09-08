#include "Modifier.h"

Modifier::Modifier(Melody * melody)
{
    set(melody);
}

void Modifier::set(Melody *base)
{
    _base = base;
}

Melody *Modifier::get()
{
    return _base;
}
