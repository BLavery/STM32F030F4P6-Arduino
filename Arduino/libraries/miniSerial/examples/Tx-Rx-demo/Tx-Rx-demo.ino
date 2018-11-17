// echo function

#include <miniSerial.h>



unsigned long t0;

void setup(void)
{
      Serial.begin(9600);
      // Serial.begin(19200, PA2, PA3);
	  pinMode(LED_BUILTIN, OUTPUT);
	  delay(500);  // IDE's serial terminal may take a bit of wakeup time. Don't lose first chrs. 
	  t0 = millis();   // used by loop()
	  Serial.print("\nminiSerial RX/TX demo - software based, non native Serial port.\n");
	  Serial.print("Transmit is unbuffered, Receive is buffered.\n");
	  Serial.print("Type some input. Demo: Buffer is read each second.\n");

}

void loop()
{
	Serial.run();    // ESSENTIAL FOR RX BUFFERING SYSTEM. and no delay() allowed below.
	
	// can't use delay() so delay by a non-blocking method !!!
	unsigned long t1 = millis();
	if (t1-t0 < 1000) // 1 sec
	    return; 
	t0 = t1;
	    
	// here only every 1 sec:    
    digitalWrite(LED_BUILTIN, 1-digitalRead(LED_BUILTIN));
	int ch;
	while ((ch=Serial.read())>=0) // read any/all chrs from buffer
	{
          Serial.print("From buffer: ");
		  Serial.println(ch);   // send it back out
	}
}
