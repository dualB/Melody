#include "ModifierTie.h"

ModifierTie::ModifierTie(Sequence *note) : Modifier(note)
{

}

int ModifierTie::isTieOrBreath() {
    int tieOrBreath = get()->isTieOrBreath();
    return tieOrBreath == 0 ? 1:tieOrBreath;
}