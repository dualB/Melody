#ifndef MelodyToSound_h
#define MelodyToSound_h

/******************************************************************************
* Definitions
******************************************************************************/
class MelodyToSound
{

public:
    static unsigned int getFrequency(int index);
    static unsigned long getDuration(unsigned long base_duration, unsigned int numerator, unsigned int denominator);

private:
    MelodyToSound(){};
};

#endif
