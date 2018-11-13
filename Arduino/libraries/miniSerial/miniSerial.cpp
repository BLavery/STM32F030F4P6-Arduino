
// A bit-banged low-footprint serial transmit/receive 
// primarily for low-memory STM32F030F4P6    BL Nov 2018
// By default uses PA9 as TX    PA10 as RX   -- regular 4-pin RX/TX end connector.
// 8 bit no parity.  19200 seems ideal (default)

// tx will block during character transfer (abt 0.6 mSec each chr at 19200)
// Your loop() must have free-running Serial.run(). No delay()s. Serial reception will suffer otherwise
// reception is buffered
// Transmit is not buffered, but does NOT stop reception processing.

// Functions in this "Serial" are NOT LIKE ARDUINO regular Serial calls.

// V 0.2.0



#include <miniSerial.h>
#include <charQueue.h>

Queue rxBuf;
//Queue txBuf;  // Buffered tx not currently implemented

MiniSerial::MiniSerial(void)
{
        

}

void MiniSerial::begin(int baud, int tx, int rx)
{
	pinRx = rx;
	pinTx = tx;
	bitDelay = (unsigned long) (1000000 / baud);
	pinMode(pinTx, OUTPUT);	
	digitalWrite(pinTx, HIGH);
    pinMode(pinRx, INPUT);
}



void MiniSerial::txStr(char * str, bool lf)             // TX a C string
{
	for (int i = 0; i<strlen(str); i++)
		_putChar(str[i]);
    if(lf) txStr("\n");

}

void MiniSerial::txByte(unsigned char ch, bool lf)             // TX a C byte
{
	_putChar(ch);
    if(lf) txStr("\n");

}

void MiniSerial::txInt(int j, bool lf)                  // TX an int (as string)
{
	_txNum(j, 10, lf);
}

void MiniSerial::txBin(int j, bool lf)              
{
	_txNum(j, 2, lf);
}

void MiniSerial::txHex(int j, bool lf)              
{
	_txNum(j, 16, lf);
}


int MiniSerial::rxChar(void) // -1 =nothing/empty
{
	// fetch from buffer
	return rxBuf.dequeue();

}



void MiniSerial::run(void)  // MUST be called VERY frequently from your loop()
{
	int ch = _getChar();
	if(ch >=0)
	    rxBuf.enqueue((char) ch);
}

///////////////////////////////////////////////////////////////////

void MiniSerial::_txNum(int j, int bits, bool lf)       // generic numeric formatting       
{
    char buffer[30];
    itoa(j,buffer,bits); 
    txStr(buffer);
    if(lf) txStr("\n");

}


int MiniSerial::_getChar(void) // bit-bang rx
// >=0 good rx char 
{
	if(pinTx<0) return ERRNOTBEGIN;
	
	switch (rxState) {
		case RXIDLE :
			if (digitalRead(pinRx))  // still idle
				return RXNONE;
			// ok, we start rx:
		    rx_reftime = micros() - bitDelay/2;
		    rx_chr = 0;
		    rxState = READING;  
		    rx_k = 0;
		    return RXBUSY;
			break;
		
		case  READING :  // 10 bit-length passes
			if(micros()-rx_reftime < bitDelay)
				return RXBUSY;
			rx_chr |= (digitalRead(pinRx) << rx_k++);
			rx_reftime += bitDelay;	
			if (rx_k > 9)
				rxState = COMPLETE; 
			return RXBUSY;
			break;
			
		case COMPLETE :
			rxState = RXIDLE; 
			if ((rx_chr & 0b01000000001) != 0b01000000000)  // start & stop bits correct?
				return ERRFRAME;
			return (int) (rx_chr & 0x1FE) >> 1;  // a good chr received
			
        default:
			break;
	}
}


void MiniSerial::_putChar(unsigned char data)    // TX one byte bit-bang
{
	if(pinTx<0) return;
	
  unsigned long starttime= micros();
  int chr = (data <<1) | 0b011000000000 ;

  for (int i=11; i>0; i--)          // 1 start (0), 8 data bits, 2 stop (11)
  {
    digitalWrite(pinTx, chr&1);  
    chr = (chr >> 1);           
    while (micros()-starttime<bitDelay) {
		run(); // keep processing incoming characters!!
	}     
    starttime += bitDelay;  
  }
}


MiniSerial mSerial; 




