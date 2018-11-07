# STM32F030F4P6-Arduino

THIS IS NOT AN OFFICIAL ARDUINO PROJECT

<img align="right" src="STM32F030-Dev-Brd.jpg">Nov 2018. This is an interim project 
for getting the "Minimal" or "Demo" board STM32F030F4P6
up and running on Arduino IDE.  I expect that the STM32duino project may shortly release 
support for this chip, in which case then use the official version, of course.  Pin numbering might 
not be identical on the official version.

## Programming?

The USB micro connector is power only, not USB data. The only practical programming method is STLink.
Get one. Check elsewhere if you need any setup. 
Get it running for your scenario, and programming becomes trivially easy thereafter. Simply leave the BOOT0 jumper always on the GND side.
And with STLink, no bootloader is used or needed.

And get a CP210x TTL USB serial adapter while you are at it. You are going to need that for "terminal."

## Libraries Included Here:

<img align="right" src="P1070122.JPG">The F030F4 has only 16K of flash. Compiling the arduino IDE with an empty sketch will use about 9 or 10K. 
However, #including any of arduino's regular Serial, Wire, SPI, will also add many K each to the build size, breaking the 16K limit.
The most obvious implication is that we now have no way to "view" any output, even any debug information,
beyond toggling a LED!  No serial terminal. Not connected at USB connector. 
Driver software too big to use TX/RX and USB Serial adapter.

There are three hacked-together arduino libraries included here, so that we can communicate 
with the F030F4, despite HAL Serial and HAL Wire being unavailable. These libraries are:

 - SerialBB - a simple software (bit-bang) duplex serial driver, default 19200. 
      So a terminal can be used.
 - WireBB - a limited software I2C driver. 1-byte data write only. 
 - oledf103f4 - a basic driver for the ubiquitous '0.96" I2C SSD1306 Oled' display, using WireBB.
      So we can see some output. Derived out of Daniel Turton's OzOled project.

Quality = hacked together, code not even tidied up yet.  But they are working.
Code size = comfortable in our tiny flash space.
These libraries were intended for exactly this purpose (arduino ide / STM32F030F4P6)
and no thought was made to adapting to other purposes (which may be quite practical, though).
Feel welcome!

## Installation:

<img align="right" src="P1070121.JPG">
1. You must install the STM32 core (official) board support from here:
   https://github.com/arduino/Arduino/wiki/Unofficial-list-of-3rd-party-boards-support-urls#list-of-3rd-party-boards-support-urls
   If you have an earlier version than 1.4, then upgrade it to 1.4.
   
   
2. Find your install location for the STM32 package (mine on Mint was /opt/Arduino1.8.5/portable/packages/STM32/hardware/STM32/1.4.0/
but yours will be doubtless a bit different. Hunt for a bunch of "variant.h" files and then check
you are indeed in the STM32 region. On my Windows machine I found the files here:  C:\Users\Brian\AppData\Local\Arduino15\packages\STM32\hardware\stm32\1.4.0\

a. inside the .../1.4.0/variants/ folder, add the DEMO-F030F4 folder from here, with its 5 files.

b. in the .../1.4.0/ folder, open the existing boards.txt in an editor, and patch in the GenF030 "excerpt" section.

3. Find your user sketchbook folder ("(documents).../Arduino/" probably, but File/Preferences in your IDE should tell you.
In its libraries folder, add the 3 libraries supplied here.


## Digital pin numbering:

  PA0  D0 
  
  PA1  D1 
  
  PA2  D2  - 
  
  PA3  D3  - 
  
  PA4  D4  - On-board LED
  
  PA5  D5  - SCK   SCL
  
  PA6  D6  - MISO  SDA  
  
  PA7  D7  - MOSI  
  
  PB1  D8  - SS
  
  PA9  D9  - TX UART Header
  
  PA10 D10 - RX UART Header
  
  D11 - not for use
  
  D12 - not for use
  
  PA13 D13 - SWDIO  - STlink Header
  
  PA14 D14 - SWCLK  - STlink header
  

## Analog pins:

A0	D15 ~ D0

A1	D16 ~ D1

A2	D17 ~ D2

A3	D18 ~ D3

A4	D19 ~ D4

A5	D20 ~ D5

A6	D21 ~ D6

A7	D22 ~ D7

A8	D23 ~ D8

	
Serial/I2C/SPI pins listed above are nominal. See file variant.h.
Suggest use the listed pins if emulating those functions in sketch software.
The library codes above use these pins.

## Regarding Serial: 

in variant.h, we have #define SERIAL_UART_INSTANCE    0 -- it could be changed to 1
You MIGHT get HAL Serial module to run (with barely flash left for anything else).
If you do activate inbuilt HAL Serial, then expect conflict with "Serial" as used in lib SerialBB.

## Wiring Hint:

In the middle pic above showing (clone) STLink and USB Serial adapter, with BOTH CONNECTED AT ONE TIME, I leave off the +3V wire of the USB-Serial device. Otherwise the STM32 board gets 3V supply from 2 sources. Haven't tested it (!), but that sounds like a "BAD IDEA!"

## Acknowledgement:

The above code for IDE support is NEARLY identical to here:
    https://github.com/stm32duino/Arduino_Core_STM32/issues/165
    
... except for different (more consistent?) PA13 = D13  PA14 = D14, 
preserving RX and TX where they are marked as such on the end header (PA9, PA10),
keeping SDA/SCL off the serial header,
and disabling the HAL Serial code.


