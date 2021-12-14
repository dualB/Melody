/*
  Melody for limited memory devices

  One melody is created and will be played using the Tone() and noTone() functions.
  During playback, informations will be sent via the Serial monitor.
  On ESP platforms, the functions are created at the end of the example.

  Since the memory of smaller microcontrolers is limited, 
  you habe to un-comment the melody you want to try, one at a time.

  More information on the MELO notation here : https://github.com/dualB/Melody

  by Claude Bouchard
  November 2020
  Modified : December 2021
*/
#include "Melody.h"

#define SERIAL_BAUDRATE 115200
#define PIN_TONE 12


//Wolfgang Amadeus Mozart, Eine kleine Nachtmusik (KV 525)
Melody melody("g<<r-d- | g<< r-d-(g<dg<b)-d<*r | c*<<r-a-c*<<r-a- |(c*<af#<a)-d<r", 140);

//John Williams, The Imperial March (Darth Vader's theme)
//Melody melody(" (ggg e,-. b,-- | g e,-. b,-- g+ (ddde,-.)* b,--  | g, e,-. b,-- g+");

//Scale with ascending loudness
//Melody melody("c>>> d>> e>f g< a<< b<<< c*<<<<", 240);

//Valid choice kind-of sound
//Melody melody(" (cgc*)**---");

//Invalid choice kind-of sound
//Melody melody(" (cg_)__");

//Frere Jacques
//Melody melody("(cdec)x2   (efgr)x2   ((gagf)-ec)x2     (c g_ c+)x2");

//Au Clair de la Lune
//Melody melody(" ( (cccde+dr  ceddc+.r)x2  dddd (a+ar)_ dc(b a g+.r)_ cccde+dr ceddc+.r )*");

// John Sebastian Bach, The Musical Offering Theme
//Melody melody(" (((ce,ga,b_)+rg(f#fee,.)+  dd,c (ba-g-)_ c f e,+d+c+))>>+", 240);

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    #ifdef ESP_PLATFORM
        #define CHANNEL 5
        ledcSetup(CHANNEL, 5000, 8);
        ledcAttachPin(PIN_TONE, CHANNEL);
        ledcWrite(CHANNEL, 0); //duty Cycle de 0
    #endif
}

void loop()
{
    play(melody);

}

void play(Melody melody)
{

    Serial.print("Melody length : ");
    Serial.println(melody.length()); //Get the total length (number of notes) of the melody.

    melody.restart(); //The melody iterator is restarted at the beginning.

    while (melody.hasNext()) //While there is a next note to play.
    {
        melody.next(); //Move the melody note iterator to the next one.

        printInfo(melody);

        unsigned int frequency = melody.getFrequency(); //Get the frequency in Hz of the curent note.
        unsigned long duration = melody.getDuration();  //Get the duration in ms of the curent note.
        unsigned int loudness = melody.getLoudness();   //Get the loudness of the curent note (in a subjective relative scale from -3 to +3).
                                                        //Common interpretation will be -3 is really soft (ppp), and 3 really loud (fff).
        int noteIndex = melody.getNoteIndex();          //Get the index of the note.

        if (frequency > 0)
        {
            tone(PIN_TONE, frequency);
            setLoudness(loudness);
        }
        else
        {
            noTone(PIN_TONE);
        }

        delay(duration);

        //This 1 ms delay with no tone is added to let a "breathing" time between each note.
        //Without it, identical consecutives notes will sound like just one long note.
        noTone(PIN_TONE);
        delay(1);
    }

    noTone(PIN_TONE);
    delay(1000);
}

void printInfo(Melody melody)
{
    Serial.print(melody.index() + 1); //Get the index of the current note.
    Serial.print("/");
    Serial.print(melody.length());
    Serial.print(" : ");
    Serial.print(melody.getFrequency());
    Serial.print("Hz (index ");
    Serial.print(melody.getNoteIndex());
    Serial.print("), ");
    Serial.print(melody.getDuration());
    Serial.print(" ms, ");
    Serial.print(melody.getLoudness());
    Serial.print(" loud.\n");
}

void setLoudness(int loudness){
    //Loudness could be use with a mapping function, according to your buzzer or sound-producing hardware
   #ifdef ESP_PLATFORM
      #define MIN_HARDWARE_LOUDNESS 0
      #define MAX_HARDWARE_LOUDNESS 16
      ledcWrite(CHANNEL, map(loudness, -4, 4, MIN_HARDWARE_LOUDNESS, MAX_HARDWARE_LOUDNESS));
   #endif

}


#ifdef ESP_PLATFORM

    void tone(int pin, int frequency) //FOR ESP Platform, pin is unused
    {
        ledcWriteTone(CHANNEL, frequency);
    }
    void noTone(int pin) //FOR ESP Platform, pin is unused
    {
        ledcWrite(CHANNEL, 0);
    }

#endif