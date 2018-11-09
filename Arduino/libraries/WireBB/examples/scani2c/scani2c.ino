#include "WireBB.h"
#include <SerialBB.h>

void setup()
{
	Wire.begin();
	delay(500);
	Serial.txStr("I2C scan:\n\n");
	for (byte i=10; i<0x78; i++)
	{
		Wire.beginTransmission(i);
		if(!Wire.endTransmission())
		{
			Serial.txStr("0x");
			Serial.txHex(i, true);
		}
	}
	Serial.txStr("\nThat's all.\n");
}


void loop()
{
	
}
