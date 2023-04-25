#include <FastLED.h>
#include <Keypad.h>

#define LED_PIN 13
#define NUM_LEDS 300

CRGB leds[NUM_LEDS];


  //Gets the individual numpad buttons
char keypad[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[4] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[4] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
boolean dontStopGradient = false;

int colors[4][3] = {
    {200, 200, 200},
    {100, 100, 100},
    {50, 50, 50},
    {50, 100, 200}
} ;
Keypad membraneKeypad = Keypad( makeKeymap(keypad), rowPins, colPins, 4, 4); //Creates the keypad
// List of colors for the gradient on testLEDs()
int gradientA[21][3] = {
    {153, 0, 76},
    {204, 0, 102},
    {255, 51, 51},
    {255, 0, 0},
    {255, 153, 51},
    {255, 128, 0},
    {255, 255, 51},
    {128, 255, 0},
    {51, 255, 51},
    {0, 255, 128},
    {0, 153, 76},
    {51, 255, 255},
    {0, 255, 255},
    {102, 178, 255},
    {0, 128, 255},
    {0, 76, 153},
    {0, 0, 153},
    {0, 0, 102},
    {102, 0, 204},
    {76, 0, 153},
    {51, 0, 102}
} ;


int gradient[7][3] = { // 2D array of colors (RGB values)
  {255, 0, 0}, // red
  {255, 127, 0}, // orange
  {255, 255, 0}, // yellow
  {0, 255, 0}, // green
  {0, 0, 255}, // blue
  {75, 0, 130}, // indigo
  {148, 0, 211} // violet
};

void e(){
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB(0,255,0);
    FastLED.show();
    delay(10);    
  }
}

void gradientCycle() {
  String anq;
  int gradientIndex = 0; // start at the first color in the gradient
  int step = 0; // start at the beginning of the gradient
  while (dontStopGradient) { // loop until another key is pressed
      anq = membraneKeypad.getKey();
      // set the current LED to the color at the current step in the gradient
      leds[step] = CRGB(gradient[gradientIndex][0], gradient[gradientIndex][1], gradient[gradientIndex][2]);
      // increment the step
      step++;
      // if we've reached the end of the LED array, start over at the beginning
      if (step == NUM_LEDS) {
        step = 0;
      }
      // increment the gradient index
      gradientIndex++;
      // if we've reached the end of the gradient, start over at the beginning
      if (gradientIndex == 7) {
        gradientIndex = 0;
      }
      // display the LED array
      FastLED.show();
      // wait for a short amount of time before cycling to the next color
      delay(10);
      if(anq == 'NO_KEY'){
        dontStopGradient = true;
        Serial.println("nk");
      }else if(anq == 'A'){
        dontStopGradient = true;
        Serial.println("a");
      }else{
        dontStopGradient = false;
        Serial.println(anq);
      }
    

  }
}



/**This is to test the LEDs. It will go through the gradientA array and set the LEDs to the colors in the array. 
*@param numLEDS is the number of LEDs you would like to test.
*Currently configured to test LEDs that have GRB color order (for some reason).
*/
void testLEDs(int numLEDS){ 
    for(int q = 0; q < 21; q++){
        for(int i = 0; i < numLEDS; i++){
            leds[i] = CRGB(gradientA[q][1], gradientA[q][0], gradientA[q][2]);
            FastLED.show();
            delay((3)); //This cycles the LED's to make it a nice gradient. The delay is in milliseconds.
        }
        delay(500);
    }
    fill_solid(leds, NUM_LEDS, CRGB(0,255,0));
    delay(2000);
}

// This does an auto  gradient. It takes in the number of LEDs, the colors, the delay time, and the period (ie. how long it takes to go through the gradient(cycles). If it was 1 it would go through the gradient one time per strip.
/**
 * This is a function that will do an auto gradient.
 * @param numLeds is the number of LEDs in the stri
 * @param colors is the 2D array of colors that you want to use in the gradient.
 * @param delayTime is the time in milliseconds that you want to wait between each LED lighting up.
 * @param period is the number of times you would like to cycle through the colors per @param numleds leds.
*/

void autoGradient(int delayTime, double period){
  if(!dontStopGradient){
    int totColors = sizeof gradientA / sizeof gradientA[0];   //This is to get the total number of colors in the array
    Serial.println(totColors);   
    int CPP = NUM_LEDS / totColors; //This is to get the number of LEDs per color
    Serial.println(CPP);
    double DBCP = (period * CPP); // This
    Serial.println(DBCP);
  
    for(int q = 0; q< totColors; q++){
        for(double rt = 0; rt < NUM_LEDS; rt+=DBCP){
            for(int j = 0; j<DBCP; j++){
                leds[(int)rt+j] = CRGB(gradientA[q][0], gradientA[q][1], gradientA[q][2]);
                
                
            }
        }
        FastLED.show();
        delay(delayTime);
    }           
  }
}



void setup(){
    Serial.begin(9600);
   

    //This is to make sure that the colors are not out of range
    for(int i = 0; i < sizeof colors / sizeof colors[0]; i++){
        for(int j = 0; j< sizeof colors[0] / sizeof(int); j++){
            if(colors[i][j] > 256){
                colors[i][j] = 256;
            }else if(colors[i][j] < 0){
                colors[i][j] = 0;
            }
        }
    }

    //Here we are adding the leds. The first number is the type of led, so in this case WS2812B. The second is the pin, and the third is the color order.
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);

    //testLEDs(NUM_LEDS);
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
    FastLED.show();
    delay(2000);
    FastLED.clear();  // clear all pixel data
    FastLED.show();
    e();
    FastLED.clear();
}

void loop(){
    char customKey = membraneKeypad.getKey(); // This is to get the key that is pressed, if no key is pressed it will return NO_KEY. This is kind of like getButtonPressed() in the other code
    

  
    switch (customKey){
        case 'NO_KEY':
            Serial.println("No key is being pressed");
            
            break;
        case '1':
            dontStopGradient = false;
            Serial.println("1 is being pressed");
            leds[0] = CRGB(colors[0][0],colors[0][1], colors[0][2]);
            FastLED.show();
            break;
        case '2':
            dontStopGradient = false;
            Serial.println("2 is being pressed");
            leds[0] = CRGB(colors[1][0],colors[1][1], colors[1][2]);
            FastLED.show();
            break;
        case '3':
            dontStopGradient = false;
            Serial.println("3 is being pressed");
            leds[0] = CRGB(colors[2][0],colors[2][1], colors[2][2]);
            FastLED.show();
            break;
        case '4':
            dontStopGradient = false;
            Serial.println("4 is being pressed");
            leds[0] = CRGB(colors[3][0],colors[3][1], colors[3][2]);
            FastLED.show();
            break;
        case 'A':
            dontStopGradient = true;
            Serial.println("A is being pressed");
            //autoGradient(100, .33);
            gradientCycle();
            break;
    }


}   
