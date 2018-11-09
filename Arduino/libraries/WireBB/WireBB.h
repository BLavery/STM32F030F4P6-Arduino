
#pragma once

#ifndef _WIREBB_
#define _WIREBB_

#define BUFFER_LENGTH 32
#include "twi.h"

class WireBB {
  private:
    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;
    
    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;
    void flush(void);


  public:
    WireBB (void);
    void begin();
    void beginTransmission(int address);
    int endTransmission(bool sendStop=true);
    int write(char ch);
    int write(char* str);
    int write(char* data, int datalen);
    uint8_t requestFrom(uint8_t address, uint8_t size, bool sendStop = true);
	int read(void);
	int available(void);

	
};

extern WireBB Wire;

#endif
