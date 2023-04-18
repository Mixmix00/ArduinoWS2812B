#include <FastLED.h>

#define LED_PIN 9
#define NUM_LEDS 100

CRGB leds[NUM_LEDS];


  


int colors[4][3] = {
{200, 200, 200},
{100, 100, 100},
{50, 50, 50},
{50, 100, 200}
} ;





void setup(){
    for(int i = 0; i < sizeof colors / sizeof colors[0]; i++){
        
        for(int j = 0; j< sizeof colors[0] / sizeof(int); j++){
            if(colors[i][j] > 256){
                colors[i][j] = 256;
            }else if(colors[i][j] < 0){
                colors[i][j] = 0;
            }
        }
    }

    FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop(){

    
    //If(button pressed on numpad){
        //Then change to color} else if(button pressed on numpad){
            //Then change to other color}...
    


    //If we wanted to add that you have to press and hold you could maybe add an else at the end or create a boolean and if one num on the numpad is pressed disable everything
    // here, so
    leds[0] = CRGB(colors[0][0],colors[0][1], colors[0][2]);
    FastLED.show();


}