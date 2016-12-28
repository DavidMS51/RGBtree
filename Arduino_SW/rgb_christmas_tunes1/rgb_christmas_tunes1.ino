/*
    David Saul 2016  (https://meanderingpi.wordpress.com/)
    Christmas tunes played on Andrew Gales RGBtree  (http://www.pocketmoneytronics.co.uk/)
    Developed from code written by;
      Raj Madhuram ( http://geekraj.com ) -  who Adapted the melody code by Tom Igoe
      NeoPixel Ring simple sketch (c) 2013 Shae Erisson
      [released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library]

      Notes from various places (acknowledged inline)

    Use with Microbit version of RGBtree
    Connect LED terminal to D6, Sound to D8, switch between D2 and gnd   [NO push)
    requires Adafruit_NeoPixel.h to be installed in the same sub-directory as the main program

   - This application was developed to use with Arduino Uno, I have not tested with any-other Arduino h/w
   - The complier will report low memory warning, this does not seem to cause any problems in practice

*/

// Neopixel stuff
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// max Brightness limit   [ max = 255 ]
// WARNING Neopixels put out a lot of light, do not look directly at the Neopixels when using high Brightness settings
// I reccomend you keep the BRIGHT to 40 or less   [ I find 20 is fine ]
#define BRIGHT 20

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);
// For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

#include "pitches.h"

typedef struct {
  int *melody;
  int *durations;
  int numCount;
  int tempo;
  int low, high;
} tune;

tune tunes[5];

// Jingle Bells
int jingleBells[] = { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
                      N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, N_G5,
                      N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
                      N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, N_C5
                    };
int jingleBellsDurations[] = { 4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
                               4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
                               4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
                               4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16
                             };

// The first noel
// http://www.music-for-music-teachers.com/support-files/first-noel-broken-chord-stretch-key-of-c.pdf

int firstNoel[] = { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
                    N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
                    N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
                    N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
                    N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_C5, N_B4, N_A4, N_A4,
                    N_G4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4
                  };

int firstNoelDurations[] = { 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
                             8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                             8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
                             8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                             8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 8, 4,
                             12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8
                           };

// O Holy Night
// http://www.music-for-music-teachers.com/support-files/o-holy-night-lead-sheet-c.pdf

int oHolyNight[] = { N_E4, N_E4, N_E4, N_G4, N_REST, N_G4, N_A4, N_A4, N_F4, N_A4, N_C5,
                     N_G4, N_G4, N_E4, N_D4, N_C4, N_E4, N_F4, N_G4, N_F4, N_D4, N_C4,
                     N_E4, N_E4, N_E4, N_G4, N_REST, N_G4, N_A4, N_A4, N_F4, N_A4, N_C5,
                     N_G4, N_G4, N_FS4, N_E4, N_B4, N_G4, N_A4, N_B4, N_C5, N_B4, N_E4, N_REST, N_G4,
                     N_G4, N_A4, N_D4, N_G4, N_A4, N_G4, N_C5, N_E4, N_A4, N_G4, N_G4, N_G4, N_A4,
                     N_D4, N_G4, N_A4, N_G4, N_C5, N_E4, N_G4, N_C5, N_C5, N_B4, N_A4,
                     N_B4, N_A4, N_REST, N_A4, N_D5, N_D5, N_A4, N_A4, N_A4, N_C5,
                     N_C5, N_REST, N_C5, N_E5, N_D5, N_D5, N_G4, N_C5, N_C5, N_B4, N_A4,
                     N_G4, N_G4, N_G4, N_A4, N_G4, N_G4, N_G4, N_C5, N_D5,
                     N_D5, N_G4, N_E5, N_E5, N_D5, N_C5, N_B4, N_C5, N_D5,
                     N_C5
                   };

int oHolyNightDurations[] = { 6, 4, 2, 8, 2, 2 , 4, 2, 4, 2, 12,
                              4, 2, 4, 2, 6, 4, 2, 6, 4, 2, 24,
                              6, 4, 2, 8, 2, 2 , 4, 2, 4, 2, 12,
                              4, 2, 4, 2, 6, 4, 2, 6, 4, 2, 20, 2, 2,
                              6, 6, 6, 6, 4, 2, 4, 2, 6, 4, 2, 6, 6,
                              6, 6, 4, 2, 4, 2, 12, 12, 6, 4, 2,
                              12, 8, 2, 2, 12, 4, 2, 4, 2, 12,
                              8, 2, 2, 12, 8, 2, 2, 12, 6, 4, 2,
                              12, 4, 2, 4, 2, 12, 6, 6, 12,
                              6, 6, 12, 6, 6, 12, 6, 4, 2,
                              24
                            };

// http://www.christmas-carol-music.org/Lead_Sheets/WeThreeKings.html

int weThreeKings[] = { N_B4, N_A4, N_G4, N_E4, N_FS4, N_G4, N_FS4, N_E4,
                       N_B4, N_A4, N_G4, N_E4, N_FS4, N_G4, N_FS4, N_E4,
                       N_G4, N_G4, N_G4, N_A4, N_A4, N_B4, N_B4, N_D5, N_C5, N_B4,
                       N_A4, N_B4, N_A4, N_G4, N_FS4, N_E4,
                       N_FS4, N_A4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4,
                       N_G4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_B4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4
                     };

int weThreeKingsDurations[] = { 4, 2, 4, 2, 2, 2, 2, 6,
                                4, 2, 4, 2, 2, 2, 2, 6,
                                2, 2, 2, 4, 2, 4, 2, 2, 2, 2,
                                2, 2, 2, 4, 2, 6,
                                6, 6, 4, 2, 4, 2, 4, 2, 6, 4, 2, 4, 2, 4, 2, 6,
                                4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 6
                              };

// What child is this
// http://www.free-scores.com/PDF_EN/traditional-what-child-is-this-39593.pdf

int whatChild[] = { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_B3, N_REST,  N_E4,
                    N_G4, N_A4, N_B4, N_C4, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST,
                    N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, N_REST,
                    N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4
                  } ;

int whatChildDurations[] = { 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 6, 2, 2, 2,
                             4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4, 2,
                             6, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 4, 2,
                             6, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4
                           };

const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;
int toneNum = 0;
int randomOffset = 0;
int outputStartPin = 3;
int continuousMode = 0;

int tune_tmp = 0;

// setup for random led display
int l =  random(5);
int lt = 10;    // mkae sure l <> lt on start
int c = random(8);
int ct = 10;

void play(int tuneNum) {

  randomOffset = random(32);

  int numNotes = tunes[tuneNum].numCount;
  int tempo = tunes[tuneNum].tempo;
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {

    int freq = tunes[tuneNum].melody[thisNote] * 2;
    int noteDuration = tempo * tunes[tuneNum].durations[thisNote];

    if (freq > 0) {
      int n = (map(freq, tunes[tuneNum].low, tunes[tuneNum].high, 1, 31) + randomOffset) % 31 + 1;
      ran_led();
      tone(8, freq, noteDuration);

    } else {
      // REST
      delay(noteDuration);
    }

    delay(noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 0.30;
    delay(pauseBetweenNotes);

    noTone(8);

  }
}

void ran_led() {          // changes a neopixel at random avoiding repeats
  while (l == lt) {
    l = random(5);
  }
  lt = l;
  while (c == ct) {
    c = random(7) + 1;
  }
  ct = c;
  set_led(l, c);
}

void clear_led() {      // display a simple seqence then clear neopixels to off
  for (int l = 0; l < 6 ; l++) {
    set_led(l, 9);
    delay(100);
  }

}

void setup() {

  //Serial for debugging
  //Serial.begin(9600);
  //Serial.println("Starting App");

  randomSeed(analogRead(0));

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();   // make sure everything is off to start

  int numTunes = 5;

  tunes[0].melody = jingleBells;
  tunes[0].durations = jingleBellsDurations;
  tunes[0].numCount = sizeof(jingleBells) / sizeof(int);
  tunes[0].tempo = 60;

  tunes[1].melody = firstNoel;
  tunes[1].durations = firstNoelDurations;
  tunes[1].numCount = sizeof(firstNoel) / sizeof(int);
  tunes[1].tempo = 60;

  tunes[2].melody = oHolyNight;
  tunes[2].durations = oHolyNightDurations;
  tunes[2].numCount = sizeof(oHolyNight) / sizeof(int);
  tunes[2].tempo = 100;

  tunes[3].melody = weThreeKings;
  tunes[3].durations = weThreeKingsDurations;
  tunes[3].numCount = sizeof(weThreeKings) / sizeof(int);
  tunes[3].tempo = 100;

  tunes[4].melody = whatChild;
  tunes[4].durations = whatChildDurations;
  tunes[4].numCount = sizeof(whatChild) / sizeof(int);
  tunes[4].tempo = 100;

  for (int i = 0; i < numTunes; i++) {
    int low = N_DS8;
    int high = 0;
    for (int j = 0; j < tunes[i].numCount; j++) {
      int freq = tunes[i].melody[j];
      if (freq != 0 && freq < low) low = freq;
      if (freq > high) high = freq;
    }
    tunes[i].high = high;
    tunes[i].low = low;
  }

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);


}

void playTune() {

  while (toneNum == tune_tmp) {     //pick a tune at random but don't repeat
    toneNum = random(5);
  }
  tune_tmp = toneNum;
  play(toneNum);

;
}

void loop() {
  int count = 0;
  if (continuousMode) {
    playTune();
    delay(2000);
  }
  else {
    while (count < 2000) {
      delay(1);
      count = count + 1;
      // read the state of the pushbutton value:
      buttonState = digitalRead(buttonPin);
      // check if the pushbutton is pressed.
      // if it is, the buttonState is LOW:
      if (buttonState == LOW) {
        clear_led();
        playTune();
        count = 0;
        delay(500);
        clear_led();
      }
    }
    ran_led();
    count = 0;
  }
}
