#ifndef SimpleMelody_h
#define SimpleMelody_h

#include "Melody.h"
#include "EmptyMelody.h"
#include "Note.h"

/******************************************************************************
* Definitions
******************************************************************************/
struct Node
{
	Melody *melody;
	struct Node *next;
};

class SimpleMelody : public Melody
{

public:
	SimpleMelody();
	~SimpleMelody();
	void addMelody(Melody *);

	bool hasNext();
	void restart();
	void next();
	int length();

	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensityIndex();

private:
	Node *_head;
	Node *_cursor;

};

#endif
