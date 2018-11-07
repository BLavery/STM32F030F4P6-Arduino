
#pragma once

#ifndef _WIREBB_
#define _WIREBB_

#define BUFFER_LENGTH 32
#include "twi.h"

class WireBB {
  private:
    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;


  public:
    WireBB (void);
    void begin();
    void beginTransmission(int address);
    int endTransmission(bool stop=true);
    int write(char ch);
    int write(char* str);
    int write(char* data, int datalen);

	

	
};

extern WireBB Wire;

#endif
