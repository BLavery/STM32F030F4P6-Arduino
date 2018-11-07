
#ifndef SI2C_h
#define SI2C_h
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_OK                      0
#define I2C_SCL_HELD_LOW            1
#define I2C_SCL_HELD_LOW_AFTER_READ 2
#define I2C_SDA_HELD_LOW            3
#define I2C_SDA_HELD_LOW_AFTER_INIT 4

void twi_init();
void twi_stop(void);
uint8_t twi_writeTo(unsigned char address, unsigned char * buf, unsigned int len, bool sendStop);


#ifdef __cplusplus
}
#endif

#endif
