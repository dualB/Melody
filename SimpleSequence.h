#ifndef SimpleSequence_h
#define SimpleSequence_h

#include "Sequence.h"
#include "EmptySequence.h"
#include "Note.h"

/******************************************************************************
* Definitions
******************************************************************************/
struct Node
{
	Sequence *sequence;
	struct Node *next;
};

class SimpleSequence : public Sequence
{

public:
	SimpleSequence();
	~SimpleSequence();
	void addSequence(Sequence *);

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
