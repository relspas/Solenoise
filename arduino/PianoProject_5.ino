/* Piano Project (soon to be renamed)
   This code created by Justin Kelman, 6/22/16
   The project is in collaboration with Raphael Elspas.

   The circuit:
   Solenoids (1A each) are each powered by a 12V supply run in series with an NMOS,
   with diodes across the solenoid leads in the reverse direction to prevent arcing.
   The NMOS gates are connected to digital pins, with a 10K pull down resistor to ground.

   The code takes a vector of binary numbers as input that represents piano keys to be played at set 
   time intervals. Each bit corresponds to a specific note on the piano. 
   At each time step, the solenoids are set high for when a key is pressed,
   and set low when a key is not pressed.
 */
#include "mendel_op30_2_compressed.h"
#include <avr/pgmspace.h>
//const byte musicarray PROGMEM = {music};

//int songlength = sizeof(music)/sizeof(byte)/8;   //Number of time steps of whole piece

const int nkeys = 60;
unsigned long prevTime = 0;
int digout[] = {LOW,HIGH};
int t=0;
int i;
//int offset=29;
byte music[8];
int repeat=0;

void setup() {
  for (i=4;i<=53;i++){
  pinMode(i, OUTPUT);  //So the TX/RX pins 0 and 1 flash HIGH for a moment when the program starts, so for testing we start with pin 2
 }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT); 
//  Serial.begin(9600);
//  Serial.println(songlength);
}

void loop() {
  while (t<songlength){
    unsigned long currentTime = millis();//Test, compare with delay()
    if (currentTime - prevTime >= interval) {
      prevTime = currentTime;

      if (repeat==0){
        for (i=0;i<8;i++){
           music[i]=pgm_read_byte(&musicarray[t][i]);
        }
        repeat = bitRead(music[7],0)+bitRead(music[7],1)*2+bitRead(music[7],2)*4+bitRead(music[7],3)*8+1;
        t=t-repeat+1;
      }
      readline(music);
      t++;
      repeat--;
    }
  }
  //End of song 
//  delay(interval);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
  digitalWrite(A8, LOW);
  digitalWrite(A9, LOW);

  for (i=4;i<=53;i++){
    digitalWrite(i, LOW);
  }
  while(1){};
}

void readline(byte music[]){
  int by,bi;
  int note=4;

  digitalWrite(A0, digout[bitRead(music[0],7)]);
  digitalWrite(A1, digout[bitRead(music[0],6)]);
  digitalWrite(A2, digout[bitRead(music[0],5)]);
  digitalWrite(A3, digout[bitRead(music[0],4)]);
  digitalWrite(A4, digout[bitRead(music[0],3)]);
  digitalWrite(A5, digout[bitRead(music[0],2)]);
  digitalWrite(A6, digout[bitRead(music[0],1)]);
  digitalWrite(A7, digout[bitRead(music[0],0)]);
  digitalWrite(A8, digout[bitRead(music[1],7)]);
  digitalWrite(A9, digout[bitRead(music[1],6)]);
   for (bi=5; bi>=0;bi--){
         digitalWrite(note, digout[bitRead(music[1],bi)]);  //This is the byte version
         note++;
    }
    for (by=2;by<=6;by++){
      for (bi=7; bi>=0;bi--){
       //if (note-offset>=2){
         digitalWrite(note, digout[bitRead(music[by],bi)]);  //This is the bin version      
      //}
         note++;
      }
    }
    for (bi=7; bi>=4;bi--){
         digitalWrite(note, digout[bitRead(music[7],bi)]);  //This is the byte version
         note++;
    }
}
