<h1> WS2182B LED Keypad Controller</h1>
<h3>This is a simple Arduino project that controls a strip of WS2812B LEDs using a 4x4 membrane keypad. The code includes a function to test the LEDs by cycling through a predefined color gradient. The user can then select a color from a pre-defined set of colors using the keypad.</h3>

<h2>Requirements</h2>
    a) Arduino board<br>
    b) Protocol WS2812B LED strip<br>
    c) 4x4 membrane keypad
<h2>Libraries Required</h2>
    a)FastLED (included with Arduino IDE or can be downloaded from the FastLED GitHub)<br>
    b)Keypad (can be downloaded from the Arduino Library Manager or from the Keypad GitHub)
<h2>Usage</h2>
This code allows you to press a button to make an LED change color.<br>
You can also use a method to do a gradient
<h2>Notes</h2>
The code includes a function to limit the color values to a range of 0-255. If your LED strip for some god awful reason uses a different color range, you may need to modify the code accordingly.
<h3>Contributors</h3>
Max Spier <strong>(<a href="https://github.com/TTVMixmix00/">Github</a>)</strong>
