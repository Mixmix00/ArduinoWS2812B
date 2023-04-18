int colors[4][3] = {
{200, 200, 200},
{100, 100, 100},
{50, 50, 50},
{50, 100, 200}
} ;





void setup(){
    for(int i = 0; i < sizeof colors / sizeof colors[0]; i++){
        //Serial.println();
        for(int j = 0; j< sizeof colors[0] / sizeof(int); j++){
            //Serial.print(colors[i][j]);
        }
    }
}

void loop(){
    //If(button pressed on numpad){
        //Then change to color} else if(button pressed on numpad){
            //Then change to other color}...
    


    //If we wanted to add that you have to press and hold you could maybe add an else at the end or create a boolean and if one num on the numpad is pressed disable everything



}