// for stm32f030f4p6
// bitbang i2c
// modelled on 8266 code
// V 0.0.2

#include "WireBB.h"
#include "Arduino.h"

uint8_t WireBB::rxBuffer[BUFFER_LENGTH];
uint8_t WireBB::rxBufferIndex = 0;
uint8_t WireBB::rxBufferLength = 0;

uint8_t WireBB::txAddress = 0;
uint8_t WireBB::txBuffer[BUFFER_LENGTH];
uint8_t WireBB::txBufferIndex = 0;
uint8_t WireBB::txBufferLength = 0;

uint8_t WireBB::transmitting = 0;

WireBB::WireBB(void)
{};


void WireBB::begin()
{
		twi_init(); 
		flush();
};

void WireBB::beginTransmission(int address)
{          
//	if (transmitting)
//	    twi_init();                                
  transmitting = 1;
  txAddress = address;
  txBufferIndex = 0;
  txBufferLength = 0;	 
};

int WireBB::endTransmission(bool sendStop)
{

  int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, sendStop);
  digitalWrite(SDA, LOW) ; pinMode(SDA, OUTPUT);
  txBufferIndex = 0;
  txBufferLength = 0;
  transmitting = 0;     
  return ret;	
};

int WireBB::write(char data)
{
  if(transmitting){
    if(txBufferLength >= BUFFER_LENGTH){
      return 0;
    }
    txBuffer[txBufferIndex] = data;
    ++txBufferIndex;
    txBufferLength = txBufferIndex;
  }

  return 1;
	
};

int WireBB::write(char* str)
{
	return write(str, strlen(str));	
};

int WireBB::write(char* data, int quantity)
{
  if(transmitting){    
    for(size_t i = 0; i < quantity; ++i){
      if(!write(data[i])) 
          return i;
    }
  }
  return quantity;
	
};

uint8_t WireBB::requestFrom(uint8_t address, uint8_t size, bool sendStop){
  if(size > BUFFER_LENGTH){
    size = BUFFER_LENGTH;
  }
  size_t read = (twi_readFrom(address, rxBuffer, size, sendStop) == 0)?size:0;
  rxBufferIndex = 0;
  rxBufferLength = read;
  return read;
}

void WireBB::flush(void)
{
	rxBufferIndex = 0;
	rxBufferLength = 0;
	txBufferIndex = 0;
	txBufferLength = 0;
	
}

int WireBB::read(void)
{
	int value=-1;
	if(rxBufferIndex < rxBufferLength)
	{
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}
	return value;
}

int WireBB::available(void)
{
	return rxBufferLength - rxBufferIndex;
}

WireBB Wire;

