// Serial BitBash for STM32F030F4P6

#pragma once

#define BITDELAY  52 
//  104 9600  baud  52 19200    26  38400 


class SerialBB
{
  public:
	SerialBB(void);
	void txByte(unsigned char data, bool lf=false);
	void txStr(char * str, bool lf=false);
	void txInt(int j, bool lf=false) ;
	void txBin(int j, bool lf=false) ;
	void txHex(int j, bool lf=false) ;
	char rxChar(void);
	int  getChar(void);
	void run(void);
  private:
  	void _putChar(unsigned char ch);
  	char _rx; // buffered chr
	char _rx1 = 0;


};

extern SerialBB Serialbb; 
#define Serial Serialbb
