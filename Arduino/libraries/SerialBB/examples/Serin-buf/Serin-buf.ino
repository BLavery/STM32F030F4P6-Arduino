// echo function

#include <SerialBB.h>



unsigned long t0;

void setup(void)
{
	  pinMode(LED_BUILTIN, OUTPUT);
	  t0 = millis();
	  Serial.txStr("\nBuffered Serial In  - Echo\n");
}

void loop()
{
	Serial.run();
	
	unsigned long t1 = millis();
	if (t1-t0 < 3000) // 3 sec
	    return; 
	t0 = t1;
	    
	// only every xx passes:    
    digitalWrite(LED_BUILTIN, 1-digitalRead(LED_BUILTIN));
	int ch;
	while (ch=Serial.rxChar()) // read any chrs from buffer
	{
          Serial.txStr("From buffer: ");
		  Serial.txInt(ch, true);   // send it back out
	}
}
