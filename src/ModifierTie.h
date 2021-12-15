#ifndef ModifierTie_h
#define ModifierTie_h

#include "Modifier.h"
/******************************************************************************
 * Definitions
 ******************************************************************************/
class ModifierTie : public Modifier
{

public:
	ModifierTie( Sequence *note = nullptr);
	int isTieOrBreath();

protected:
private:

};

#endif
