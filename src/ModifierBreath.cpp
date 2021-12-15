#include "ModifierBreath.h"

ModifierBreath::ModifierBreath(unsigned int denom, Sequence *note) : Modifier(note)
{
    _isTie = denom < 0;
    _denominator = denom > 0  ? denom : 1;
    _numerator = denom > 0 || _isTie ? 1 : 0;
    _isBreathingNow = false;
}

bool ModifierBreath::hasNext()
{
    return (!_isTie && !_isBreathingNow) || get()->hasNext();
}
void ModifierBreath::restart()
{
    _isBreathingNow = false;
    get()->restart();
}
void ModifierBreath::next()
{
    if (_isTie)
    {
        get()->next();
    }
    else
    {

        if (_isBreathingNow)
        {
            _isBreathingNow = false;
            get()->next();
        }
        else
        {
            _isBreathingNow = true;
        }
    }
}

int ModifierBreath::length()
{
    return 2 * get()->length();
}

unsigned int ModifierBreath::getDurationNumerator() { return  _isBreathingNow ? _numerator : get()->getDurationNumerator() * _denominator - _numerator * get()->getDurationDenominator(); }
unsigned int ModifierBreath::getDurationDenominator() { return _isBreathingNow ? _denominator : get()->getDurationDenominator() * _denominator; }
bool ModifierBreath::isRest() { return _isBreathingNow; }