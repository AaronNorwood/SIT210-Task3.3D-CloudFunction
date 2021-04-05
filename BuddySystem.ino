#include "Particle.h"

int led = D5; 
bool wave = false;
bool pat = false;
int i = 0;

void setup() {
    pinMode(led, OUTPUT);
    //subscribe to the event and define the response type
    Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", eventHandler);
}

void loop() {
    //response to wave signal
    if(wave){
        i = 0;
        //flash 3 times more slowly
        while(i < 3)
        {
            digitalWrite(led, HIGH);
    
            delay(100);
            
            digitalWrite(led, LOW);
              
            delay(100);
            i++;
        }
        wave = false;
    }
    //response to pat signal
    if(pat){
        i = 0;
        //flash 6 times quickly
        while(i < 6)
        {
            digitalWrite(led, HIGH);
    
            delay(50);
            
            digitalWrite(led, LOW);
              
            delay(50);
            i++;
        }
        pat = false;
    }
   
}

void eventHandler(const char *event, const char *data)
{
    String message = String(data).toLowerCase();
    //check if signal is a wave
    if(message == "wave")
    {
        wave = true;
    }
    //check if pat
    else if(message == "pat")
    {
        pat = true;
    }
    else
    {
        Particle.publish("signal was neither pat nor wave");
    }
}
