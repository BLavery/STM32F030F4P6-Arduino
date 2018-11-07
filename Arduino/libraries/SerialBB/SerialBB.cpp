
// A very rough bit-banged serial transmit for STM32F030F4P6    BL Nov 2018
// Uses PA9 as TX    PA10 as RX   -- regular 4-pin RX/TX end connector.
// 8 bit no parity.  19200 seems ideal

// both tx and rx will block during character transfer (abt 0.6 mSec each chr at 19200)
// Functions in this "Serial" are NOT LIKE ARDUINO regular Serial calls.

// V 0.0.1


#include <SerialBB.h>
#include <Arduino.h>

// we use a simple fifo/ring buffer for rx
#define BUFFER_SIZE 32
#define TYPE char
// https://www.embeddedrelated.com/showcode/292.php   
#include "c__buf.h"
// & DONT instantiate more than 1 serial object. (single circ buffer outside class)

SerialBB::SerialBB(void)
{
	pinMode(PIN_SERIAL_TX, OUTPUT);	
	digitalWrite(PIN_SERIAL_TX, HIGH);
    pinMode(PIN_SERIAL_RX, INPUT);

}



void SerialBB::_putChar(unsigned char data)    // TX one byte
{
  unsigned long starttime= micros();
  digitalWrite(PIN_SERIAL_TX, 0);           // make start bit
  while (micros()-starttime < BITDELAY) {} ;  
  for (int i=8; i>0; i--)          // 8 serial bits
  {
    digitalWrite(PIN_SERIAL_TX, data&1);  
    data = (data >> 1);           
    starttime += BITDELAY;  
    while (micros()-starttime<BITDELAY) {} ;    
  }
  digitalWrite(PIN_SERIAL_TX, 1);           // dbl stop bit
  starttime += BITDELAY;  
  while (micros()-starttime < (BITDELAY*2)) {} ;    
}


void SerialBB::txByte(unsigned char ch, bool lf)             // TX a C char
{
	_putChar(ch);
    if(lf) txStr("\n");

}

void SerialBB::txStr(char * str, bool lf)             // TX a C string
{
	for (int i = 0; i<strlen(str); i++)
		_putChar(str[i]);
    if(lf) txStr("\n");

}

void SerialBB::txInt(int j, bool lf)                  // TX an int (as string)
{
    char buffer[20];
    itoa(j,buffer,10); 
    txStr(buffer);
    if(lf) txStr("\n");
}

void SerialBB::txBin(int j, bool lf)              
{
    char buffer[30];
    itoa(j,buffer,2); 
    txStr(buffer);
    if(lf) txStr("\n");

}

void SerialBB::txHex(int j, bool lf)              
{
    char buffer[20];
    itoa(j,buffer,16); 
    txStr(buffer);
    if(lf) txStr("\n");

}

char SerialBB::rxChar(void) // 0=nothing
{
	// fetch from buffer
	return getElement();

}

void SerialBB::run(void)
{
	int ch = getChar();
	if(ch >0)
	    addElement((char) ch);
}

int SerialBB::getChar(void) // -1: nothing    -2 = stop/start framing error     >=0 good rx char 
{
	// raw, unbuffered
	unsigned long int chr = 0; 
	unsigned long reftime= micros() - BITDELAY/2;  
	if (digitalRead(PIN_SERIAL_RX))  // idle
	    return -1;
    // falling edge of start bit
	for (int k=0; k<=9; k++)
	{
		while (micros()-reftime < BITDELAY)  
		    ; // wait   
		chr |= (digitalRead(PIN_SERIAL_RX) << k);
		reftime += BITDELAY;
	}
	if ((chr & 0b01000000001) != 0b01000000000)  // start & stop bits correct?
		return -2;
	return (int) (chr & 0x1FE) >> 1;
	
}

SerialBB Serialbb; 




