#include <Adafruit_NeoPixel.h>
#include <midiusb.h>
#define NUM_LEDS = 75


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)





const int interruptPin = 2; //the momentary button should be wired directly to this pin and to the ground
volatile int selector = 1;  //this variable will be iterated by the interrupt. Volatile qualifier allows the selector to incrememnt. 
int LEDpin = 6;             //Pin for LED strip

  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LEDpin, NEO_GRB + NEO_KHZ800); //initializes the LED strip



void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  

  pinMode(interruptPin, INPUT_PULLUP);                                      //the interruptPin is initialized with the pull-up resistor enabled
  attachInterrupt (digitalPinToInterrupt(interruptPin), next, RISING);      //attaches interrupt handler
  
  
}


//main function. edit effect parameters (color, time etc.)


void loop(){

  switch (selector){
  
    case 1: Twinkle(0xff, 0xff, 0xff, 10, 100, true);        //white 
    break;

    case 2: TwinkleRandom(20, 200, true);                     //random
    break;

    case 3: Twinkle(0xeb, 0x28, 0xa3, 10, 100, false);        //pink EB28A3
    break;  

    case 4: CylonBounce(0x12, 0xa1, 0x3d, 4, 10, 50);         //12A13D green
    break; 

    case 5: TwinkleRandom(20, 200, true);                     //random
    break;

    case 6: Twinkle(0xff, 0xb3, 0x19, 10, 100, false);        //ffb319 yellow
    break;

    case 7: Twinkle(0xff, 0x00, 0x00, 10, 100, false);        //red
    break;

    case 8: CylonBounce(0x12, 0xa1, 0x3d, 4, 50, 50);         //12A13D green & faster
    break;

    case 9: SnowSparkle(0xeb, 0x28, 0xa3, 20, 200);           //EB28A3
    break;  

    case 10: Twinkle(0x1a, 0x0b, 0x9e, 10, 100, false);       //1A0B9E dark blue
    break;

    case 11: Twinkle(0x4e, 0xc8, 0xfc, 10, 100, false);       //4EC8FC light blue
    break;

    case 12: Twinkle(0x1a, 0x0b, 0x9e, 10, 100, false);       //1A0B9E dark blue
    break;

    case 13: SnowSparkle(0xeb, 0x28, 0xa3, 20, 200);          //EB28A3 pink
    break;
            
    case 14: Twinkle(0xfc, 0xe0, 0xc0, 10, 100, false);       //FCE0C0 amber
    break;

    case 15: Twinkle(0xff, 0xff, 0xff, 10, 100, false);       //white
    break;
    
    case 16: rainbowCycle(20);                                //rainbow
    break;  

    case 17: Twinkle(0xff, 0x00, 0x00, 10, 100, false);       //red
    break;

    case 18: Twinkle(0xfc, 0xe0, 0xc0, 10, 100, false);       //FCE0C0 amber
    break;

    case 19: Twinkle(0x1a, 0x0b, 0x9e, 10, 100, false);       //1A0B9E dark blue
    break;

    case 20: TwinkleRandom(20, 200, true);                    //random
    break;

    case 21: Strobe(0xff, 0xff, 0xff, 10, 50, 1000);          //strobe
    break;
    
    case 23: selector = 1;                                    //returns to case 1
    break;
  }
}


//BEGIN STROBE

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
  delay(EndPause);
}

 
//END STROBE

//BEGIN SPARKLE

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}


//END SPARKLE

//START RANDOM COLOR TWINKLE


void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  delay(SpeedDelay);
}

//END RANDOM COLOR TWINKLE

//START RAINBOW CYCLE


void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

//END RAINBOW CYCLE

//START SNOW SPARKLE


void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red,green,blue);
  
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,0xff,0xff,0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
}

//END SNOW SPARKLE

//START COLOR TWINKLE


void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

//END COLOR TWINKLE

//START CYLON BOUNCE

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}


//END CYLON NOUNCE
//END EFFECTS USED IN SWITCH





//used to advance the cases by increments of 1, using the pushbutton

void next()   {
  selector++;
}



void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
  
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));

 
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}