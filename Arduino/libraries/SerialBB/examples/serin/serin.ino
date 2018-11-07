// echo function

#include <SerialBB.h>


void setup(void)
{
	  pinMode(LED_BUILTIN, OUTPUT);
	  Serial.txStr("\nSerial In (& Out) - Echo\n");
}

void loop()
{
	int ch = Serial.getChar(); // read any chr uncoming - not buffered
	if (ch >= 0)
	{
		// it's good. do something
		  digitalWrite(LED_BUILTIN, 1-digitalRead(LED_BUILTIN));
		  Serial.txByte(ch, true);   // send it back out
	}
}
