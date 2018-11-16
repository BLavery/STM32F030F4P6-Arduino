// Serial BitBash for STM32F030F4P6

#pragma once

#include <Arduino.h>

#define BITDELAY  52 
//  104 9600  baud  52 19200  
//  not good above 19200

#define HEX 16
#define BIN 2
#define OCT 8

class MiniSerial
{
  public:
	MiniSerial(void);
	void begin(int baudrate = 19200, int txpin = PA9, int rxpin = PA10);
	int  read(void);
	void run(void);
    void write(unsigned char data);
    void print(double float_num, int prec=2);	// uses lots of flash space! Avoid?
	void print(char* str);
    void print(int, int = DEC);
    void print(long, int = DEC);
    void println(double float_num, int prec=2);	
	void println(char* str = "");  // handles println() also
    void println(int, int = DEC);
    void println(long, int = DEC);

  private:

	int  _getChar(void);
  	char _rx; // buffered chr
	char _rx1 = 0;
	int pinTx= -1;  // -1 = not begin'd
	int pinRx ;
	unsigned long bitDelay = 52;  // //  104 9600  baud  52 19200  

	enum { RXIDLE, READING, COMPLETE } ;
	enum { RXBUSY = -4, ERRNOTBEGIN = -3, ERRFRAME = -2,  RXNONE = -1 }; 
	int rxState = RXIDLE;
	unsigned long rx_chr = 0; 
	unsigned long rx_reftime = 0;
	int rx_k;

};

extern MiniSerial mSerial; 
#define Serial mSerial
