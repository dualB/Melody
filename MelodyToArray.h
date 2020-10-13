#ifndef MelodyToArray_h
#define MelodyToArray_h


#define MAX_ARRAY_LENGTH = 1024;
struct Sound{
    unsigned int frequency;
    unsigned long duration;
    int loundness;
};


#include "Arduino.h"
#include "Melody.h"
/******************************************************************************
* Definitions
******************************************************************************/
class MelodyToArray  
{

public: 
    MelodyToArray();
    Sound* convert(Melody *,unsigned int ,HardwareSerial*);

private: 
    unsigned int getFrequency(int);
    void log(Sound,HardwareSerial*);
    unsigned long getDuration(unsigned long, unsigned int, unsigned int ,HardwareSerial*);
};


#endif
