/*
  Melody with Serial

  With the Serial monitor, you can send a string using the MELO notation, and a melody will be created and played based on it.
  During playback, informations will be sent via the Serial monitor.
  On ESP platforms, the functions are created at the end of the example. 

  More information on the MELO notation here : https://github.com/dualB/Melody

  by Claude Bouchard
  November 2020
*/

#include "Melody.h"

#define SERIAL_BAUDRATE 115200

#define PIN_TONE 12

#ifdef ESP_PLATFORM
  #define CHANNEL 5
  #define MIN_HARDWARE_LOUDNESS 0
  #define MAX_HARDWARE_LOUDNESS 16
#endif



void setup()
{
  Serial.begin(SERIAL_BAUDRATE);

  #ifdef ESP_PLATFORM
    ledcSetup(CHANNEL, 5000, 8);
    ledcAttachPin(PIN_TONE, CHANNEL);
    ledcWrite(CHANNEL, 0); //duty Cycle de 0
  #endif
}

void loop()
{
  if (Serial.available())
  {

    String melo = Serial.readString();

    Melody *melody = new Melody(melo);
    play(melody);
    delete melody;
  }
}

void play(Melody* melody)
{

    Serial.print("Melody length : ");
    Serial.println(melody->length()); //Get the total length (number of notes) of the melody.

    melody->restart(); //The melody iterator is restarted at the beginning.

    while (melody->hasNext()) //While there is a next note to play.
    {
        melody->next(); //Move the melody note iterator to the next one.

        printInfo(melody);

        unsigned int frequency = melody->getFrequency(); //Get the frequency in Hz of the curent note.
        unsigned long duration = melody->getDuration();  //Get the duration in ms of the curent note.
        unsigned int loudness = melody->getLoudness();   //Get the loudness of the curent note (in a subjective relative scale from -3 to +3).
                                                        //Common interpretation will be -3 is really soft (ppp), and 3 really loud (fff).

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

void printInfo(Melody *melody)
{
  Serial.print(melody->index() + 1); //Get the index of the current note.
  Serial.print("/");
  Serial.print(melody->length());
  Serial.print(" : ");
  Serial.print(melody->getFrequency());
  Serial.print("Hz, ");
  Serial.print(melody->getDuration());
  Serial.print(" ms, ");
  Serial.print(melody->getLoudness());
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