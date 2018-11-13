# STM32F030F4P6-Arduino

THIS IS NOT AN OFFICIAL STM32/ARDUINO PROJECT

<img align="right" src="STM32F030-Dev-Brd.jpg">This is an __interim project__ 
for getting the STM32F030F4P6 Cortex-M0 "Minimum System Dev" or "Demo" board 
up and running on Arduino IDE.  eBay and AliExpress are flooded with these for $2.  This may be a 32-bit chip at 48MHz, but it is the baby of the STM32 line.

I expect that the STM32duino project may shortly release 
support for this chip, in which case then use the official version, of course.  

In any case, the library modules in this project should still be valid on an official support version.

## Programming?

The USB micro connector is for 5V power only, not USB data. 

The only practical programming method is STLink.
**Get one** ($3). Check elsewhere if you need any config/setup help. 
Get it running for your scenario, and programming becomes trivially easy thereafter. Simply leave the BOOT0 jumper always on the GND side.
And with STLink, no bootloader is used or needed. (And that's a whole other hassle out of the way!)

And get a 3V TTL USB serial adapter (CP2102 and CH340 are 3V) while you are at it ($1.5). You are going to need that for "terminal."

## Libraries Included Here:

<img align="right" src="P1070122.JPG">The F030F4 has only 16K of flash. Compiling the arduino IDE with an empty sketch will use about 8K. 
However, including calls in your sketch to arduino's regular __Serial__ will also add __many K__ to the build size, breaking the 16K limit. And HAL __Wire__ conflicts with the regular uart header use.

The most obvious implication is that we now have no easy way to "view" any output, even any debug information,
beyond toggling a LED!  (No serial terminal. It's not connected at USB connector. 
And the native Serial Driver software is too big.)

There are some new lightweight arduino libraries included here, so that we now **can** communicate 
with the F030F4. We can run a "Serial" on its uart header, and we can run an oled display with a "Wire" on i2c pins of our choice. These libraries (with example files) are:

 - __miniSerial__ - a simple software non-interrupt duplex serial driver, default 19200. 
      So a terminal can be used. TXD/RXD ie PA9/PA10, ie at the correct uart header, but pin configurable if needed.
      Some info:  https://github.com/BLavery/miniSerial
 - __miniOled__ - a lean and basic driver for the ubiquitous '0.96" I2C SSD1306 Oled' display, using I2C writes via SoftWire.
      So we can see some output. Derived out of Daniel Turton's OzOled project 2014/2015. You need to also fetch and 
      install other-party libraries SoftWire and AsyncDelay, which drive the I2C.

Quality = working, if not elegant. 
Code size = comfortable in our tiny flash space.
The library code is intentionally minimal - just enough to get the job done, of being able to "talk"
to this board. 

Other Libraries, needed for miniOled:
 - __SoftWire__ 2.0 from here: https://www.arduinolibraries.info/libraries/soft-wire
 - __AsyncDelay__ (used by SoftWire) from here: https://github.com/stevemarple/AsyncDelay


## Installation:
<img align="right" src="P1070121.JPG">

1. You must install the STM32 core (official) board support from here:
   https://github.com/arduino/Arduino/wiki/Unofficial-list-of-3rd-party-boards-support-urls#list-of-3rd-party-boards-support-urls
   If you have an earlier version than 1.4, then upgrade it to 1.4.  (1.4 is current as at this date 7 Nov.)

2. Find your install location for the STM32 package (mine on Mint was /opt/Arduino1.8.5/portable/packages/STM32/hardware/STM32/1.4.0/
but yours will be doubtless a bit different. Hunt for a bunch of "variant.h" files and then check
you are indeed in the STM32 region. On my Windows install I found the files here:  C:\Users\Brian\AppData\Local\Arduino15\packages\STM32\hardware\stm32\1.4.0\

a. inside the .../1.4.0/variants/ folder, add the DEMO-F030F4 folder from here, with its 5 files. (Now - 12 Nov - aligned with coming V1.5.)

b. in the .../1.4.0/ folder, open the existing boards.txt in an editor, and patch in the GenF030 "excerpt" section.

3. Find your user sketchbook folder ("(documents).../Arduino/" probably, but File/Preferences in your IDE should tell you).
In its libraries folder, add the libraries supplied here, and the SoftWire & AsyncDelay ones too.


## Digital pin numbering: 

(Revised 12 Nov)

In your sketch, pins can be referenced by any of (for LED, for example) PA4,  D4  or just 4. I find using PA4 style to be intuitive as it agrees with the board markings.

  PA0  D0 
  
  PA1  D1 <img align="right" src="ss66.jpg">
  
  PA2  D2  
  
  PA3  D3  
  
  PA4  D4  = On-board LED
  
  PA5  D5  
  
  PA6  D6  
  
  PA7  D7  - 
  
  PB1  D8  - 
  
  PA9  D9  = UART Header "TX" 
  
  PA10 D10 = UART Header "RX" 
  
  PA13 D11 - SWDIO  = STlink Header "DIO"
  
  PA14 D12 - SWCLK  = STlink header "CLK"
  

## Analog pins: 

(Revised 12 Nov)

A0	~ PA0

A1	~ PA1

A2	~ PA2

A3	~ PA3

A4	~ PA4

A5	~ PA5

A6	~ PA6

A7	~ PA7

A8	~ PB1

	
## Wiring Hint:

In the second pic above showing USB Serial adapter and (clone) STLink, with BOTH CONNECTED AT ONE TIME, I leave off the +3V wire of the USB-Serial device. Otherwise the STM32 board gets 3V supply from 2 sources. Haven't tested it (!), but that sounds like a "BAD IDEA!"

Note the pic also shows no USB-micro connection to the STM32 board. That would be a THIRD voltage source in this case!   The moral: Whatever is your connection configuration, THINK about where your board supply is coming from.

V. 0.3.0 13 Nov 2018

## Acknowledgement:

The above code for IDE support is now (12 Nov) the same as this (Adminius) version: 
    https://github.com/stm32duino/Arduino_Core_STM32/tree/master/variants/DEMO_F030F4 
(IE, Earlier version here has now been brought into line with forthcoming V1.5.) A couple of pin numberings have changed. 
    
The Installation parts 1 and 2 above will become obsolete/unnecessary here when 1.5 is released.
But the library files here (Installation part 3 above) will remain working and valid. 


