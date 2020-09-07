#include "ModifierDuration.h"

ModifierDuration::ModifierDuration(unsigned int numerator, unsigned int denominator)
{
    _numerator = numerator;
    _denominator = denominator;
}

unsigned int ModifierDuration::getDurationNumerator() { return _numerator * getBase()->getDurationNumerator(); }
unsigned int ModifierDuration::getDurationDenominator() { return _denominator * getBase()->getDurationDenominator(); }
