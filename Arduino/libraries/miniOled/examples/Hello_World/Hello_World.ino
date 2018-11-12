
#include <miniOled.h>

void setup(){

	delay(700);

	Oled.init();  //initialze OLED display
	Oled.wideFont = true;
	Oled.chrSpace=3;
	Oled.drawLine(3, 0xe0);
	Oled.printString("Hello",0,0); 
	Oled.printInt(F_CPU/1000000,0,5); 
	Oled.printString("MHz",0,6);
	Oled.wideFont = false;
	Oled.chrSpace=1;
	Oled.printString("Hello Brian",0,2); 
	// Oled.printString("abcdefg",5,5); 
	delay(5000);
	// Oled.clearDisplay();
	// Oled.printBigNumber("7",0,0);

	// Oled.printBigNumber("9",3,0);
	Oled.printBigNumber("2",6,4);
	Oled.printBigNumber("9",12,0);
	Oled.printBigNumber("8",9,4); 
	Oled.printBigNumber("5",12,4); 
	//Oled.setPowerOff();

}

void loop(){
  
}

