#ifndef ModifierIntensity_h
#define ModifierIntensity_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierIntensity : public Modifier
{

public:
	ModifierIntensity(int deltaIntensity, Melody *note = nullptr);
	int getIntensity();

protected:
private:
	unsigned int _deltaIntensity;
};

#endif
