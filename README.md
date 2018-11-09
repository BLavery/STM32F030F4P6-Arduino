# STM32F030F4P6-Arduino

THIS IS NOT AN OFFICIAL STM32/ARDUINO PROJECT

<img align="right" src="STM32F030-Dev-Brd.jpg">7 Nov 2018. This is an interim project 
for getting the STM32F030F4P6 Cortex-M0 "Minimum System Dev" or "Demo" board 
up and running on Arduino IDE.  eBay and AliExpress are flooded with these for $2.  This may be a 32-bit chip at 48MHz, but it is the baby of the STM32 line.

I expect that the STM32duino project may shortly release 
support for this chip, in which case then use the official version, of course.  Pin numbering might 
not be identical on the official version.

In any case, the library modules in this project should still be valid on an official support version.

## Programming?

The USB micro connector is for 5V power only, not USB data. The only practical programming method is STLink.
**Get one** ($3). Check elsewhere if you need any config/setup help. 
Get it running for your scenario, and programming becomes trivially easy thereafter. Simply leave the BOOT0 jumper always on the GND side.
And with STLink, no bootloader is used or needed.

And get a 3V TTL USB serial adapter (CP2102 and CH340 are 3V) while you are at it ($1.5). You are going to need that for "terminal."

## Libraries Included Here:

<img align="right" src="P1070122.JPG">The F030F4 has only 16K of flash. Compiling the arduino IDE with an empty sketch will use about 8K. 
However, #including any of arduino's regular __Serial__, __Wire__, or __SPI__, will also add __many K__ each to the build size, breaking the 16K limit.

The most obvious implication is that we now have no way to "view" any output, even any debug information,
beyond toggling a LED!  (No serial terminal. It's not connected at USB connector. 
And the HAL Driver software is too big, even if we used the TX/RX and USB Serial adapter.)

There are several hacked-together lightweight arduino libraries included here, so that we now **can** communicate 
with the F030F4. These libraries (with example files) are:

 - __SerialBB__ - a simple software (bit-bang) duplex serial driver, default 19200. 
      So a terminal can be used. TXD/RXD ie PA9/PA10.
 - __WireBB__ - a software I2C driver. read, 1-byte data write. PA5/PA6.
 - __oledf030f4__ - a basic driver for the ubiquitous '0.96" I2C SSD1306 Oled' display, using I2C writes via WireBB.
      So we can see some output. Derived out of Daniel Turton's OzOled project 2014/2015.
 - __ADXL345-030f4__ - "Proof of concept" of I2C input device operating using I2C reads on WireBB.

Quality = hacked together, code not even tidied up yet.  But they are working.
Code size = comfortable in our tiny flash space.
The library code is intentionally minimal - just enough to get the job done, of being able to "talk"
to this board. 
These libraries were intended for exactly this target (arduino ide / STM32F030F4P6)
and no thought was made to adapting to other purposes. (Which may be quite practical, though. Feel welcome!)

And re SPI, there is no reason that the very simple SoftwareSPI library (github/Flickerstrip) shouldn't press into service easily. So RF24 radio modules or TFT LCD displays might be manageable if we can control their code bloat.

## Installation:
<img align="right" src="P1070121.JPG">

1. You must install the STM32 core (official) board support from here:
   https://github.com/arduino/Arduino/wiki/Unofficial-list-of-3rd-party-boards-support-urls#list-of-3rd-party-boards-support-urls
   If you have an earlier version than 1.4, then upgrade it to 1.4.  (1.4 is current as at this date 7 Nov.)

2. Find your install location for the STM32 package (mine on Mint was /opt/Arduino1.8.5/portable/packages/STM32/hardware/STM32/1.4.0/
but yours will be doubtless a bit different. Hunt for a bunch of "variant.h" files and then check
you are indeed in the STM32 region. On my Windows install I found the files here:  C:\Users\Brian\AppData\Local\Arduino15\packages\STM32\hardware\stm32\1.4.0\

a. inside the .../1.4.0/variants/ folder, add the DEMO-F030F4 folder from here, with its 5 files.

b. in the .../1.4.0/ folder, open the existing boards.txt in an editor, and patch in the GenF030 "excerpt" section.

3. Find your user sketchbook folder ("(documents).../Arduino/" probably, but File/Preferences in your IDE should tell you).
In its libraries folder, add the libraries supplied here.


## Digital pin numbering:

  PA0  D0 
  
  PA1  D1 <img align="right" src="ss66.jpg">
  
  PA2  D2  - 
  
  PA3  D3  - 
  
  PA4  D4  - On-board LED
  
  PA5  D5  - SCK   SCL
  
  PA6  D6  - MISO  SDA  
  
  PA7  D7  - MOSI  
  
  PB1  D8  - SS
  
  PA9  D9  - UART Header "TXD" 
  
  PA10 D10 - UART Header "RXD" 
  
  D11 - not for use
  
  D12 - not for use
  
  PA13 D13 - SWDIO  = STlink Header "DIO"
  
  PA14 D14 - SWCLK  = STlink header "CLK"
  

## Analog pins:

A0	D15 ~ PA0

A1	D16 ~ PA1

A2	D17 ~ PA2

A3	D18 ~ PA3

A4	D19 ~ PA4

A5	D20 ~ PA5

A6	D21 ~ PA6

A7	D22 ~ PA7

A8	D23 ~ PB1

	
Serial/I2C/SPI pins listed above are nominal. 
Suggest use the listed pins if emulating those functions in sketch software.
~The library codes above implicitly use these pins as in variant.h.~

## Regarding Serial: 

in variant.h, we have the line #define SERIAL_UART_INSTANCE    __0__ -- it could be changed to 1
You MIGHT get HAL Serial module to run (with barely enough flash left for anything else).
If you do activate inbuilt HAL Serial, then expect conflict with "Serial" as used in lib SerialBB.

## Wiring Hint:

In the second pic above showing USB Serial adapter and (clone) STLink, with BOTH CONNECTED AT ONE TIME, I leave off the +3V wire of the USB-Serial device. Otherwise the STM32 board gets 3V supply from 2 sources. Haven't tested it (!), but that sounds like a "BAD IDEA!"

Note the pic also shows no USB-micro connection to the STM32 board. That would be a THIRD voltage source in this case!   The moral: Whatever is your connection configuration, THINK about where your board supply is coming from.

## Acknowledgement:

The above code for IDE support is NEARLY identical to here:
    https://github.com/stm32duino/Arduino_Core_STM32/issues/165
    
... except for different (more consistent?) PA13 = D13  PA14 = D14, 
preserving RX and TX where they are marked as such on the end header (PA9, PA10),
keeping SDA/SCL off the serial header,
and disabling the barely/not useable HAL Serial code to save precious flash.


