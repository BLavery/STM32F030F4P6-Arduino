
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
	delay(1000);
	// Oled.clearDisplay();
	Oled.printBigNumber("-31",6,4);
	Oled.printBigNumber("9",12,0);
//	delay(1000);
//	Oled.printBigNumber("8",9,4); 
//	Oled.printBigNumber("5",12,4);
	delay(1000);
	Oled.printBigNumber("   ", 6,4);  // clear those positions
	Oled.printBigNumber(62, 6,4); 
	//Oled.setPowerOff();


}

void loop(){
  
}

