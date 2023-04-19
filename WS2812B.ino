#include <FastLED.h>
#include <Keypad.h>

#define LED_PIN null
#define NUM_LEDS 100

CRGB leds[NUM_LEDS];


  //Gets the individual numpad buttons
char keypad[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

short rowPins[4] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
short colPins[4] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

int colors[4][3] = {
    {200, 200, 200},
    {100, 100, 100},
    {50, 50, 50},
    {50, 100, 200}
} ;

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

Keypad membraneKeypad;

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
void autoGradient(int numLeds, int[][] colors, int delayTime, float period){
    int totColors = sizeof colors / sizeof colors[0];   //This is to get the total number of colors in the array
    int CPP = numLeds / totColors; //This is to get the number of LEDs per color
    int DP = (period * CPP)(int); // This
    int rt = 0;
    for(int q = 0; q< totColors; q++){
        for(rt; rt < numLeds; rt+=DP){
            for(int j = 0; j<DP; j++){
                leds[rt+j] = CRGB(colors[q][0], colors[q][1], colors[q][2]);
                FastLED.show();
                delay(delayTime);
            }
        }
    }           

}



void setup(){
    Serial.begin(9600);
    membraneKeypad = Keypad( makeKeymap(keypad), rowPins, colPins, 4, 4); //Creates the keypad
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

    //Here we are adding the leds. The first number is the type of led, so in this case WS2812 the second is the pin, the third is the color order
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);

    testLEDs(NUM_LEDS);
    FastLED.clear();  // clear all pixel data
    FastLED.show();
}

void loop(){
    char customKey = membraneKeypad.getKey(); // This is to get the key that is pressed, if no key is pressed it will return NO_KEY. This is kind of like getButtonPressed() in the other code
    
    if(customKey != NO_KEY){
        Serial.println("No key is being pressed");
    }

    //If(button pressed on numpad){
        //Then change to color} else if(button pressed on numpad){
            //Then change to other color}...
    


    //If we wanted to add that you have to press and hold you could maybe add an else at the end or create a boolean and if one num on the numpad is pressed disable everything
    // here, so

    
    
    leds[0] = CRGB(colors[0][0],colors[0][1], colors[0][2]);
    FastLED.show();


}