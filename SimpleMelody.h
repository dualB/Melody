#ifndef SimpleMelody_h

#define SimpleMelody_h

#include "Melody.h"
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
	Note *next();

public:
	Node *_head;
	Node *_cursor;
};

#endif
