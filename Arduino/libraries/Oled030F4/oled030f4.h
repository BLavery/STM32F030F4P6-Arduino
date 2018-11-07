/*
  oled030f4.h - 0.96' I2C 128x64 OLED Driver Library


*/

#ifndef OLED_data_H
#define OLED_data_H

#include <Arduino.h>

#define OLED_ADDRESS					0x3C

// registers
#define OLED_COMMAND_MODE				0x80
#define OLED_DATA_MODE				0x40

// commands
#define OLED_CMD_DISPLAY_OFF			0xAE
#define OLED_CMD_DISPLAY_ON			0xAF

#define HORIZONTAL_ADDRESSING	0x00
#define PAGE_ADDRESSING			0x02


class OLED {

public:

	byte addressingMode;
    bool wideFont = false;
    int chrSpace = 1;   // 1 -  3
	void sendCommand(byte command);
	void sendData(byte Data);

	void printChar(char c, byte X=255, byte Y=255);
	void printString(const char *String, byte X=255, byte Y=255, byte numChar=255);
	void printBigNumber(const char *number, byte column=0, byte page=0, byte numChar=255); 
    void printInt(int j, byte X=255, byte Y=255);
    void drawLine(int page, byte data);
	byte printNumber(long n, byte X=255, byte Y=255);
	byte printNumber(float float_num, byte prec=6, byte Y=255, byte numChar=255);
    void drawBitmap(const byte *bitmaparray, byte X, byte Y, byte width, byte height);
    void init();
	
	void setCursorXY(byte Column, byte Row);
	void clearDisplay();


	void setPowerOff();
	void setPowerOn();
	void setPageMode();
	void setHorizontalMode();

/*	
	void scrollRight(byte start, byte end, byte speed);
	void scrollLeft(byte start, byte end, byte speed);
	void scrollDiagRight();
	void scrollDiagLeft();
	void setActivateScroll(byte direction, byte startPage, byte endPage, byte scrollSpeed);
	void setDeactivateScroll();
*/
};

extern OLED Oled;  // OLED object 

#endif


