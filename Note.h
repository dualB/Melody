#ifndef Note_h
#define Note_h

/******************************************************************************
* Definitions
******************************************************************************/
class Note
{

public:
	Note();
	virtual int getNoteIndex();
	virtual bool isRest();
	unsigned int getDurationNumerator() { return 1; };
	unsigned int getDurationDenominator() { return 1; }
	int getIntensity() { return 0; }
};

#endif
