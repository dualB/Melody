#include "MelodyToArray.h"

MelodyToArray::MelodyToArray()
{
}

Sound *MelodyToArray::convert(Melody *melody, unsigned int tempo, HardwareSerial *printer)
{
    if (melody->length() <= 0 || tempo == 0)
    {
        return new Sound[0];
    }
    Sound *sounds = new Sound[melody->length()];
    int i = 0;
    unsigned long base_duration = (60000 / (tempo > 0 ? tempo : 1));
    printer->print("base_duration ");
    printer->println(base_duration);
    melody->restart();
    while (melody->hasNext())
    {
        printer->print("noteIndex ");
        printer->println(melody->getNoteIndex());
        printer->print("freq ");
        printer->println(getFrequency(melody->getNoteIndex()));
        sounds[i].frequency = getFrequency(melody->getNoteIndex());
        printer->print("duration ");
        printer->println(getDuration(base_duration, melody->getDurationNumerator(), melody->getDurationDenominator(), printer));
        sounds[i].duration = getDuration(base_duration, melody->getDurationNumerator(), melody->getDurationDenominator(), printer);
        sounds[i].loundness = melody->getIntensity();
        i++;
        melody->next();
    }
    for (int j = 0; j < melody->length(); j++)
    {
        MelodyToArray::log(sounds[j],printer);
    }
}

void MelodyToArray::log(Sound sound, HardwareSerial *printer)
{
    printer->print(sound.frequency);
    printer->print(", ");
    printer->print(sound.duration);
    printer->print(", ");
    printer->println(sound.loundness);
}

unsigned long MelodyToArray::getDuration(unsigned long base_duration, unsigned int numerator, unsigned int denominator, HardwareSerial *printer)
{
    printer->print("numerator ");
    printer->println(numerator);
    printer->print("denominator ");
    printer->println(denominator);
    if (denominator == 0)
    {
        return 0;
    }
    return base_duration * numerator / denominator;
}

unsigned int MelodyToArray::getFrequency(int index)
{

    const unsigned int frequenceDeBaseNote[] = {
        16,
        17,
        18,
        19,
        21,
        22,
        23,
        25,
        26,
        28,
        29,
        31,
        33,
        35,
        37,
        39,
        41,
        44,
        46,
        49,
        52,
        55,
        58,
        62,
        65,
        69,
        73,
        78,
        82,
        87,
        93,
        98,
        104,
        110,
        117,
        123,
        131,
        139,
        147,
        156,
        165,
        175,
        185,
        196,
        208,
        220,
        233,
        247,
        262,
        277,
        294,
        311,
        330,
        349,
        370,
        392,
        415,
        440,
        466,
        494,
        523,
        554,
        587,
        622,
        659,
        698,
        740,
        784,
        831,
        880,
        932,
        988,
        1047,
        1109,
        1175,
        1245,
        1319,
        1397,
        1480,
        1568,
        1661,
        1760,
        1865,
        1976,
        2093,
        2217,
        2349,
        2489,
        2637,
        2794,
        2960,
        3136,
        3322,
        3520,
        3729,
        3951,
        4186,
        4435,
        4699,
        4978,
        5274,
        5588,
        5920,
        6272,
        6645,
        7040,
        7459,
        7902,
        8372,
        8870,
        9397,
        9956,
        10548,
        11175,
        11840,
        12544,
        13290,
        14080,
        14917,
        15804,
        16744,
        17740,
        18795,
        19912,
        21096,

    };

    int finalIndex = index + 57;
    if (finalIndex < 0 || finalIndex >= 125)
    {
        return -1;
    }
    return frequenceDeBaseNote[finalIndex];
}