#ifndef Modifier_h
#define Modifier_h

#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/
class Modifier : public Note
{

public:
	Modifier();
	void setBase(Note *);
	Note *getBase();
	virtual int getNoteIndex() { return getBase()->getNoteIndex(); }
	virtual bool isRest() { return getBase()->isRest(); }
	virtual unsigned int getDurationNumerator() { return getBase()->getDurationNumerator(); }
	virtual unsigned int getDurationDenominator() { return getBase()->getDurationDenominator(); }
	virtual int getIntensity() { return getBase()->getIntensity(); }

protected:
private:
	Note *_base;
};

#endif
