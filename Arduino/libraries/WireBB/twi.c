//  B Lavery 2018
//  Derived from arduino/esp8266 file core_esp8266_si2c.c  (2015 Hristo Gochkov)
//  transmit only
// V 0.0.1
  
#include "twi.h"

#define TWI_DCOUNT  10  
// NOMINALLY (!)   Regular speed: 10 = 100khz    Faster: 3 = 330khz    
// experience: one oled happy at 3,   another flakey unless set back to 10

#define TWI_CLOCKSTRETCHLIMIT  230  //usec

#define SDA_LOW()   ({digitalWrite(TWI_SDA, LOW) ; pinMode(SDA, OUTPUT);}) //Enable SDA (becomes output and since GPO is 0 for the pin, it will pull the line low)
#define SDA_HIGH()  (pinMode(TWI_SDA, INPUT_PULLUP)) // SDA pulled up
#define SDA_READ()  ((digitalRead(TWI_SDA)) != 0)
#define SCL_LOW()   ({digitalWrite(TWI_SCL, LOW);pinMode(SCL, OUTPUT);})
#define SCL_HIGH()  (pinMode(TWI_SCL, INPUT_PULLUP))
#define SCL_READ()  ((digitalRead(TWI_SCL)) != 0)
#define DELAY()     delayMicroseconds(TWI_DCOUNT)

void twi_init(){
  SDA_HIGH();
  DELAY();
  SCL_HIGH();
  DELAY();
}

static bool twi_write_start(void) {
  SDA_HIGH();  
  if (SDA_READ() == 0) 
      return false;
  DELAY();
  SCL_HIGH();
  DELAY();
  SDA_LOW();
  DELAY();
  SCL_LOW();
  DELAY();
  return true;
}

static bool twi_write_stop(void){
  SCL_HIGH();
  uint32_t t0 = micros();
  while (SCL_READ() == 0 && (micros()-t0) < TWI_CLOCKSTRETCHLIMIT)
      ; // Clock stretching
  DELAY();
  SDA_HIGH();
  DELAY();
  //return true;
  return SDA_READ();
}

static bool twi_write_bit(bool bit) {
  bit ? SDA_HIGH() : SDA_LOW();
  DELAY();         
  SCL_HIGH();
  DELAY();
  uint32_t t0 = micros();
  while (SCL_READ() == 0 && (micros()-t0) < TWI_CLOCKSTRETCHLIMIT)
       ;// Clock stretching
  SCL_LOW();     
  DELAY();
  return true;
}

static bool twi_read_bit(void) {
  bool bit;
  SDA_HIGH();   
  DELAY();
  SCL_HIGH();
  uint32_t t0 = micros();
  while (SCL_READ() == 0 && (micros()-t0) < TWI_CLOCKSTRETCHLIMIT)
        ;// Clock stretching
  DELAY();  
  bit = SDA_READ();
  SCL_LOW();
  DELAY();
  return bit;
}

static bool twi_write_byte(unsigned char byte) {
  unsigned char bit;
  for (bit = 0; bit < 8; bit++) {
    twi_write_bit(byte & 0x80);
    byte <<= 1;
  }
  return !twi_read_bit();//NACK/ACK
}

unsigned char twi_writeTo(unsigned char address, unsigned char * buf, unsigned int len, bool sendStop){
  unsigned int i;
  if(!twi_write_start()) 
      return 4;//line busy
  if(!twi_write_byte(((address << 1) | 0) & 0xFF)) {
      if (sendStop) 
          twi_write_stop();
      return 2; //received NACK on transmit of address
  }    	
  for(i=0; i<len; i++) {
    if(!twi_write_byte(buf[i])) {
        if (sendStop) 
            twi_write_stop();
        return 3;//received NACK on transmit of data
    }
  }
  if(sendStop)  
      twi_write_stop();
  i = 0;
  while(SDA_READ() == 0 && (i++) < 10) 
  {
    SCL_LOW();
    DELAY();
    SCL_HIGH();
    DELAY();
  }
  return 0;
}
/*
unsigned char twi_readFrom(unsigned char address, unsigned char* buf, unsigned int len, unsigned char sendStop);
unsigned char twi_read_byte(bool nack);
*/
