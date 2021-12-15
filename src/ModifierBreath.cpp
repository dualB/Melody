#include "ModifierBreath.h"

ModifierBreath::ModifierBreath(unsigned int denom, unsigned int num, Sequence *note) : Modifier(note)
{
    _denominator = denom==0?16:denom;
    _numerator = num>_denominator?_denominator:num;
    _isBreathingNow = true;
}

bool ModifierBreath::hasNext()
{
    int tieOrBreath = get()->isTieOrBreath();
    return get()->hasNext() || (tieOrBreath==0 && !_isBreathingNow) ;

}

void ModifierBreath::restart()
{
    _isBreathingNow = true;
    get()->restart();
}

void ModifierBreath::next()
{
    int tieOrBreath = get()->isTieOrBreath();
    if (tieOrBreath != 0)
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

int ModifierBreath::isTieOrBreath()
{
    int tieOrBreath = get()->isTieOrBreath();
    return tieOrBreath == 0 ? -1 : tieOrBreath;
}

unsigned int ModifierBreath::getDurationNumerator()
{
    int tieOrBreath = get()->isTieOrBreath();
    
    if (tieOrBreath != 0)
    {
        return get()->getDurationNumerator();
    }
    else
    {
        if (_isBreathingNow)
        {
            return _numerator;
        }
        else
        {
            return get()->getDurationNumerator() * _denominator - _numerator * get()->getDurationDenominator();
        }
    }
}

unsigned int ModifierBreath::getDurationDenominator()
{
    int tieOrBreath = get()->isTieOrBreath();
    if (tieOrBreath != 0)
    {
        return get()->getDurationDenominator();
    }
    else
    {
        if (_isBreathingNow)
        {
            return _denominator;
        }
        else
        {
            return get()->getDurationDenominator() * _denominator;
        }
    }
}

bool ModifierBreath::isRest()
{
    int tieOrBreath = get()->isTieOrBreath();
    if (tieOrBreath != 0)
    {
        return get()->isRest();
    }
    else
    {
        return _isBreathingNow;
    }
}