#include <oled030f4.h>

void setup(){


	Oled.init();  //initialze OLED display

	Oled.printNumber((long)123, 0, 0);
delay(2000);
	Oled.setPageMode();            //Set addressing mode to Page Mode
	Oled.printNumber((long)0xFFFF, 0, 0); 
	Oled.printNumber((long)0xFFFFFFFF, 6, 0);
	Oled.printNumber((long)-12345, 3, 3);
	
}

void loop(){
  
}


