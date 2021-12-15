#include "ModifierTie.h"

ModifierTie::ModifierTie(Sequence *note) : Modifier(note)
{

}

int ModifierTie::isTieOrBreath() {
    int tieOrBreath = get()->isTieOrBreath();
    return tieOrBreath == 0 ? 1:tieOrBreath;
}

/*unsigned int ModifierTie::getDurationNumerator() {
    int tieOrBreath = get()->isTieOrBreath();
    return tieOrBreath == 0 ? 0 : get()->getDurationNumerator();
}

unsigned int ModifierTie::getDurationDenominator() {
    int tieOrBreath = get()->isTieOrBreath();
    return tieOrBreath == 0 ? 1 : get()->getDurationDenominator();
}*/