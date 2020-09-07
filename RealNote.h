#ifndef RealNote_h
#define RealNote_h

#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/
class RealNote : public Note
{

public:
	RealNote(int, bool rest = false);
	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensity();

protected:
private:
	int _index;
	bool _rest;
};

#endif
