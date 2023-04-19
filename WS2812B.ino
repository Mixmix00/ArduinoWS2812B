#include <FastLED.h>
#include <Keypad.h>

#define LED_PIN 9
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

Keypad membraneKeypad;



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
}

void loop(){

    
    //If(button pressed on numpad){
        //Then change to color} else if(button pressed on numpad){
            //Then change to other color}...
    


    //If we wanted to add that you have to press and hold you could maybe add an else at the end or create a boolean and if one num on the numpad is pressed disable everything
    // here, so

    char customKey = membraneKeypad.getKey();
    
    leds[0] = CRGB(colors[0][0],colors[0][1], colors[0][2]);
    FastLED.show();


}