
// A bit-banged low-footprint serial transmit/receive 
// primarily for low-memory STM32F030F4P6    BL Nov 2018
// By default uses PA9 as TX    PA10 as RX   -- regular 4-pin RX/TX end connector.
// 8 bit no parity.  19200 seems ideal (default)

// tx will block during character transfer (abt 0.6 mSec each chr at 19200)
// Your loop() must have free-running Serial.run(). No delay()s. Serial reception will suffer otherwise
// reception is buffered
// Transmit is not buffered, but does NOT stop reception processing.

// Functions in this "Serial" are an approximation to regular Serial calls.

// V 0.5.0



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



int MiniSerial::read(void) // -1 =nothing/empty
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




void MiniSerial::print(char* str)
{                                    
	for (int i = 0; i<strlen(str); i++)
		write(str[i]);
}

void MiniSerial::println(char* str)
{                                      
	print(str);
	print("\n");
}

void MiniSerial::print(int j, int base)
{                                      
    char buffer[30];
    itoa(j,buffer,base); 
    print(buffer);
}

void MiniSerial::print(long j, int base)  // but for stm32, both int and long are 32bit!
{                                       
    print((int)j, base);
}

void MiniSerial::println(int j, int base)
{                                       
	print(j,base);
	print("\n");
}

void MiniSerial::println(long j, int base)
{                                       
	print((int)j,base);  // long 32bit = int 32bit
	print("\n");
}

void MiniSerial::print(double float_num, int prec){
	                                       
// precision - use 6 maximum
	int d = float_num; // get the integer part
	float f = float_num - d; // get the fractional part
	if (d == 0 && f < 0.0){
		write('-');
		write('0');
		f *= -1;
	}
	else if (d < 0 && f < 0.0){
		print(d); 
		f *= -1;
	}
	else{
		print(d); 
	}
	// only when fractional part > 0, we show decimal point
	if (f > 0.0){
		write('.');
		int f_shift = 1;
		for (byte j=0; j<prec; j++){
			f_shift *= 10;
		}
		print((int)(f*f_shift)); 
	}
}

void MiniSerial::println(double float_num, int prec)
{
	print(float_num, prec);
	print("\n");
}


/////////////////////////         HARDWARE IO:

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
		
		case  READING :  // 10 bit-length passes
			if(micros()-rx_reftime < bitDelay)
				return RXBUSY;
			rx_chr |= (digitalRead(pinRx) << rx_k++);
			rx_reftime += bitDelay;	
			if (rx_k > 9)
				rxState = COMPLETE; 
			return RXBUSY;
			
		case COMPLETE :
			rxState = RXIDLE; 
			if ((rx_chr & 0b01000000001) != 0b01000000000)  // start & stop bits correct?
				return ERRFRAME;
			return (int) (rx_chr & 0x1FE) >> 1;  // a good chr received
			
        default:
			break;
	}
}


void MiniSerial::write(unsigned char data)    // TX one byte 
{
	if(pinTx<0) return;
	
  int chr = (data <<1) | 0b011000000000 ;
  unsigned long starttime= micros();

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




