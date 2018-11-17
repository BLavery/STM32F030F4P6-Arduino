
#include <miniSerial.h>


void setup() {
	Serial.begin(9600);  // defaults to 19200, tx=PA9, rx=PA10
	// Serial.begin();   // other option
	// Serial.begin(19200, PA2, PA3);  // other option
	delay(500);  // advise delay before serial output. Display wakeup reasons, not code reasons.
#ifdef STM32F030x6  //this define is board ID
    Serial.print("('030F4P6 found)\n\n");
    // original purpose of this library was for '030F4P6 board.  We found one!
#endif
	Serial.print("\nminiSerial demo.\n");


Serial.println();


}



void loop() {


	Serial.write('H');  // no linefeed, so flows on
	Serial.println("ello...");
	Serial.print(31741);
	Serial.print(" = 0x");   Serial.print(31741, HEX);
	Serial.print(" = 0b");  Serial.print(31741, BIN);
	Serial.println();
    //Serial.println(-88.445, 2); // float is very expensive in flash (3.7k)
	delay(2000);               
}
