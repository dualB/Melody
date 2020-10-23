#include "Melody.h"

#define SERIAL_BAUDRATE 115200
#define BROCHE_TONE 8

//Wolfgang Amadeus Mozart, Eine kleine Nachtmusik (KV 525)
Melody mozartNachtmusik("g<<r-d- | g<< r-d-(g<dg<b)-d<*r | c*<<r-a-c*<<r-a- |(c*<af#<a)-d<r | (gr)- g. (bag | (gag)/3:1 f#)- f#. (ac*f# | ag)- g.  (bag | (gag)/3:1 f#)- f#. (ac*f#)- | ((grgr)-- (gf#ef#)--)>> ((grgr)-- (baga)--)> | (brbr)-- (d*c*bc*)-- d*< r | ((de)+  | (d-c.)-c (c-b_.)-  b_ | (( b-a.)- a (gf#ef# | (grarbr)>)- r )_)> ", 140);

//Scale with ascending loudness
Melody scaleLouder("c>>> d>> e>f g< a<< b<<< c*<<<<", 240);

//Valid choice kind-of sound
Melody validChoice(" (cgc*)**---");

//Invalid choice kind-of sound
Melody invalidChoice(" (cg_)__");

//Frere Jacques
Melody frereJacques("(cdec)x2   (efgr)x2   ((gagf)-ec)x2     (c g_ c+)x2"); //Frère Jacques

//Au Clair de la Lune
Melody auClairDeLaLune(" ( (cccde+dr  ceddc+.r)x2  dddd (a+ar)_ dc(b a g+.r)_ cccde+dr ceddc+.r )*");

// John Sebastian Bach, The Musical Offering Theme
Melody bachMusicalOffering(" (((ce,ga,b_)+rg(f#fee,.)+  dd,c (ba-g-)_ c f e,+d+c+))>>+", 240);

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
}

void loop()
{
  play(mozartNachtmusik);
  
  play(scaleLouder);

  play(validChoice);

  play(invalidChoice);

  play(frereJacques);
  
  play(auClairDeLaLune);

  play(bachMusicalOffering);
}


void play(Melody melody)
{

    Serial.print("Melody length : ");
    Serial.println(melody.length());

    melody.restart();

    while (melody.hasNext())
    {
        melody.next();
        printInfo(melody);

        unsigned int frequency = melody.getFrequency();
        unsigned long duration = melody.getDuration();
        unsigned int loudness = melody.getLoudness();

        if (frequency > 0)
        {
            tone(BROCHE_TONE, frequency);
        }
        else
        {
            noTone(BROCHE_TONE);
        }
        delay(duration);
    }
    
    noTone(BROCHE_TONE);
    delay(1000);
}

void printInfo(Melody melody)
{
    Serial.print(melody.index() + 1);
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