#include "Melody.h"

#define SERIAL_BAUDRATE 115200

#define PIN_TONE 12
#define CHANNEL 5

#define MIN_HARDWARE_LOUDNESS 0
#define MAX_HARDWARE_LOUDNESS 16

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
  ledcSetup(CHANNEL, 5000, 8);
  ledcAttachPin(PIN_TONE, CHANNEL);
  ledcWrite(CHANNEL, 0); //duty Cycle de 0
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
      tone(frequency,loudness);
    }
    else
    {
      noTone();
    }


    delay(duration);

    //This 1 ms delay with no tone is added to let a "breathing" time between each note.
    //Without it, identical consecutives notes will sound like just one long note.
    noTone();
    delay(1);
  }

  noTone();
  delay(1000);
}

void printInfo(Melody melody)
{
  Serial.print(melody.index() + 1);  //Get the index of the current note.
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

void tone(int frequency, int loudness)
{
  ledcWriteTone(CHANNEL, frequency);
  ledcWrite(CHANNEL, map(loudness, -4, 4, MIN_HARDWARE_LOUDNESS, MAX_HARDWARE_LOUDNESS));
}
void noTone()
{
  ledcWrite(CHANNEL, 0);
}