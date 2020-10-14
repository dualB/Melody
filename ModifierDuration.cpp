#include "ModifierDuration.h"

ModifierDuration::ModifierDuration(unsigned int numerator, unsigned int denominator,Sequence *note): Modifier(note)
{
    _numerator = numerator;
    _denominator = denominator;
}

unsigned int ModifierDuration::getDurationNumerator() { return _numerator * get()->getDurationNumerator(); }
unsigned int ModifierDuration::getDurationDenominator() { return _denominator * get()->getDurationDenominator(); }
