#ifndef Note_h
#define Note_h

/******************************************************************************
* Definitions
******************************************************************************/
class Note
{

public:
	Note();
	virtual int getNoteIndex()=0;
	virtual bool isRest()=0;
	virtual unsigned int getDurationNumerator() { return 1; };
	virtual unsigned int getDurationDenominator() { return 1; }
	virtual int getIntensityIndex() { return 0; }
};

#endif
