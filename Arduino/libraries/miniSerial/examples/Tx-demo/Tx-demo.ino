
#include <miniSerial.h>


void setup() {
	Serial.begin();  // defaults to 19200, tx=PA9, rx=PA10
	// Serial.begin(9600);   // other option
	// Serial.begin(19200, PA2, PA3);  // other option
	delay(500);  // advise delay before serial output. Display wakeup reasons, not code reasons.
#ifdef STM32F030x6  //this define is board ID
    Serial.txStr("(STM32F030F4P6 board found)\n\n");
    // original purpose of this library was for '030F4P6 board.  We found one!
#endif
	Serial.txStr("\nTX demo - software based, non native Serial port.\n\n");


}



void loop() {
	//Demo of txByte, txInt, txHex, txBin, txStr
	
	Serial.txByte('H');  // no linefeed, so flows on
	Serial.txStr("ello, I'm miniSerial...", true);// optional second parameter "true" adds linefeed
	Serial.txInt(31741, true);
	Serial.txStr("0x");   Serial.txHex(31741);
	Serial.txStr(" 0b");  Serial.txBin(31741, true);
	Serial.txStr("\n");
	delay(2000);                     
}
