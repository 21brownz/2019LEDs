//includes
// #include <Wire.h>
#include <FastLED.h>

//Changeable variables
#define DATA_PIN 3
#define BRIGHTNESS 100
#define FRAMES_PER_SECOND  30
int fadeAmount = 5;
int wait = 50;
int animation = 0;
const int leftBottom = 37;
const int rightBottom = 37;
const int frontBottom = 40;
const int leftElevator = 48;
const int rightElevator = 48;

//definitions so the code knows what it's doing
//#define STRAND_LENGTH leftBottom+rightBottom+frontBottom+leftElevator+rightElevator
#define STRAND_LENGTH 122  //test strand length
int brightness = BRIGHTNESS;
CRGB leds[STRAND_LENGTH];

void setup() {
  //setup code
  // Wire.begin(8);
  // Wire.onReceive(recieveEvent);
  //Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, STRAND_LENGTH).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,6000); //not closed loop, but uses rgb values to calculate current, a little overshoot won't kill anyone
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

//just screw with stuff if you want lol
void loop() {     
      int rainFrequency = 8;
     for(int i = 0; i < rainFrequency; i++) {
        coralRain(i,0,30,false,rainFrequency);
        coralRain(i,31,50,true,rainFrequency);
        FastLED.show();
        FastLED.delay(wait);
     

     }
     
     }


void coralRain(int i, int startIndex, int endIndex, bool reverse, int rainFrequency) {
  int totalLEDs = endIndex-startIndex;
  if(reverse) {
    //for(int i = 0; i <= 5; i++) (because 5 steps(rows))
    //(totalLEDs/rainFrequency)-1
    //for(int i = rainFrequency - 1; i >= 0; i--) { //i = offset each frame

      //for(int b = 0; b < 4; b++) (number of offsets)
      for(int b = 0; b < totalLEDs/rainFrequency; b++) {
        //4 + 3*4
        leds[((rainFrequency-i-1) + b*rainFrequency)+startIndex].setRGB( 250, 75, 90);
        for(int c = 0; c < 4; c++) {
          leds[((rainFrequency-i-1+c) + b*rainFrequency)+startIndex+1].fadeToBlackBy(50);
        }
         //(scale brightness down by 196/256)
      }
      // FastLED.show();
      // FastLED.delay(wait);
    }
  //}
  //rainFrequency = 4
  //{0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9}
  //{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0}
  //{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0}
  //{0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0}
  //{0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0}
  //{0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}
  //{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0}
  else {
    //for(int i = 0; i <= 5; i++) (because 5 steps(rows))
    //(totalLEDs/rainFrequency)-1
    //for(int i = 0; i < rainFrequency; i++) { //i = offset each frame

      //for(int b = 0; b < 4; b++) (number of offsets)
      for(int b = 0; b < totalLEDs/rainFrequency; b++) {
        //4 + 3*4
        leds[(i + b*rainFrequency)+startIndex].setRGB( 250, 75, 90);
        if((i + b*rainFrequency)+startIndex > 0) {
          leds[(i + b*rainFrequency)+startIndex-1].nscale8_video(192); //(scale brightness down by 196/256)
        }
      }
      // FastLED.show();
      // FastLED.delay(wait);
    }
  //}
}

void CoralChaseBackForth() {
        for(int dot = 0; dot < STRAND_LENGTH; dot++) { 
            leds[dot].setRGB( 250, 75, 90);
            fadeToBlackBy(leds, STRAND_LENGTH, 300);
            FastLED.show();
            FastLED.delay(wait);
  }
        for(int dot = STRAND_LENGTH - 1; dot >= 0; dot--) {
            leds[dot+0].setRGB( 250, 75, 90);
            fadeToBlackBy(leds, STRAND_LENGTH, 300);
            FastLED.show();
            FastLED.delay(wait);
        }
}

void colorWipeRed() {
  for(int i=0; i<STRAND_LENGTH; i++) {
    leds[i].setRGB(128, 0, 0);
    FastLED.show();
    FastLED.delay(wait);
  }
}

void colorWipeBlue() {
  for(int i=0; i<STRAND_LENGTH; i++) {
    leds[i].setRGB(0, 0, 128);
    FastLED.show();
    FastLED.delay(wait);
  }
}

void colorWipeCoral() {
  for(int i=0; i<STRAND_LENGTH; i++) {
    leds[i].setRGB(200, 75, 90);
    FastLED.show();
    FastLED.delay(wait);
  }
}

void colorWipeBlack() {
  for(int i=0; i<STRAND_LENGTH; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
    FastLED.delay(wait);
  }
}

void elevatorChaseRed() {
  for(int dot = leftBottom+rightBottom+frontBottom; dot < leftBottom+rightBottom+frontBottom+leftElevator; dot++) { 
            leds[dot].setRGB(128, 0, 0);
            leds[dot+leftElevator].setRGB(128,0,0);
            FastLED.show();
        leds[dot] = CRGB::Black;
        leds[dot+leftElevator] = CRGB::Black;
            FastLED.delay(wait);
  }
}

void pulseRed() {

 }

// void recieveEvent(int recieveByte){
//   animation = Wire.read();
//   Serial.println(animation);
// }