#include "Melody.h"

#define SERIAL_BAUDRATE 115200
#define PIN_TONE 8


/*
 * Since the memory of smaller microcontrolers is limited, 
 * you habe to un-comment the melody you want to try, one at a time
 * 
*/

//Wolfgang Amadeus Mozart, Eine kleine Nachtmusik (KV 525)
Melody melody("g<<r-d- | g<< r-d-(g<dg<b)-d<*r | c*<<r-a-c*<<r-a- |(c*<af#<a)-d<r ", 140);

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

        if (frequency > 0)
        {
            tone(PIN_TONE, frequency);
        }
        else
        {
            noTone(PIN_TONE);
        }

        /*
        // Loudness could be use with a mapping function, according to your buzzer or sound-producing hardware
        //For Example :
        
        int realIntensity = map(loudness, -4, 4, 0, 1023);
        myBuzzer.setIntensity(realIntensity);
        */

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
    Serial.print("Hz, ");
    Serial.print(melody.getDuration());
    Serial.print(" ms, ");
    Serial.print(melody.getLoudness());
    Serial.print(" loud.\n");
}