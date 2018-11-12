#include <miniOled.h>

void setup(){
	Oled.init(6,5);  //initialze OLED display
	Oled.setHorizontalMode();      //Set addressing mode to Horizontal Mode
	Oled.printString("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");  //Print String (ASCII 32 - 126 )
	Oled.wideFont=true;
	Oled.printString("!\"#$%&'()*+,-./0123456789");  //Print String (ASCII 32 - 126 )
}

void loop(){
  
}


