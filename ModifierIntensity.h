#ifndef ModifierIntensity_h
#define ModifierIntensity_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierIntensity : public Modifier
{

public:
	ModifierIntensity(int deltaIntensity, Sequence *note = nullptr);
	int getIntensityIndex();

protected:
private:
	unsigned int _deltaIntensity;
};

#endif
