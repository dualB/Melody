#ifndef NoteToSound_h
#define NoteToSound_h

/******************************************************************************
* Definitions
******************************************************************************/
class NoteToSound
{

public:
    static unsigned int getFrequency(int index);
    static unsigned long getDuration(unsigned long base_duration, unsigned int numerator, unsigned int denominator);

private:
    NoteToSound(){};
};

#endif
