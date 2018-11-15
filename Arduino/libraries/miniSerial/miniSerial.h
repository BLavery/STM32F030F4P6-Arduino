// Serial BitBash for STM32F030F4P6

#pragma once

#include <Arduino.h>

#define BITDELAY  52 
//  104 9600  baud  52 19200    

class MiniSerial
{
  public:
	MiniSerial(void);
	void begin(int baudrate = 19200, int txpin = PA9, int rxpin = PA10);
	void txByte(unsigned char data, bool lf=false);
	void txStr(char * str, bool lf=false);
	void txInt(int j, bool lf=false) ;
	void txBin(int j, bool lf=false) ;
	void txHex(int j, bool lf=false) ;
	int  rxChar(void);
	void run(void);


	
	
  private:

  	void _putChar(unsigned char ch);
	int  _getChar(void);
  	char _rx; // buffered chr
	char _rx1 = 0;
	int pinTx= -1;  // -1 = not begin'd
	int pinRx ;
	unsigned long bitDelay = 52;  // //  104 9600  baud  52 19200    26  38400 
    void _txNum(int j, int bits, bool lf);
	enum { RXIDLE, READING, COMPLETE } ;
	enum { RXBUSY = -4, ERRNOTBEGIN = -3, ERRFRAME = -2,  RXNONE = -1 }; 
	int rxState = RXIDLE;
	unsigned long rx_chr = 0; 
	unsigned long rx_reftime = 0;
	int rx_k;

};

extern MiniSerial mSerial; 
#define Serial mSerial
