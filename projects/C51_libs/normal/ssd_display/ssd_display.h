// ssd_display.h

#ifndef _SSD_DISPLAY__H_
#define _SSD_DISPLAY__H_

#include <reg52.h>

/**
 * 	Seven-segment digit indicator library for C51 by Shurick
 *	Display numbers on 8 digit LED SSD indicator in HY-510D board
 *	Uses C51 Timer0 for synchronization - do not use this timer for other applications.
 *	NOTE: All calculations are made for 12 MHz clock.
 *	Make sure that Timer0 in C51 is NOT used by another procedure.
 *	Also whole port P1 and P2.0, P2.1 bits used for display - try not to use for other applications.
 * 	Provided Interface:
 *		void InitLEDSSD() : Initialize display before first use
 *		void Display_LSB(unsigned int number) : Show number on right side 4 digits
 *		void Display_MSB(unsigned int number) : Show number on left side 4 digits
 *		void Display_All(unsigned long number) : Show number on whole 8 digits
 */
 
/// Define output for latches:
sbit LATCH1=P2^0;
sbit LATCH2=P2^1;	   

// define buffers and constants
#define LED_SSD_DIGITS_MAX 8

// LED SSD segment pinout:
//	   0
//	 #####
// 5 # 6 # 1 
//	 #####
// 4 # 3 # 2
//	 #####	 . 7
//
/// Numbers decoded values, depends on segments pinout and board trace:
const unsigned char code digit_input[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xF7,0xFF}; // 0123456789ABCDEF_<blank>
/// Mask for segment dot:
const unsigned char code digit_iput_dot = 0x7F; // . mask
/// Segments positions, depends on segments pinout and board trace:
const unsigned char code digit_control[8]={0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};  // set digit position
/// Identifier for current active digit to show // 0..3
unsigned char current_digit = 0;
/// Digit values to show
unsigned char digit_values[LED_SSD_DIGITS_MAX]={0,0,0,0,0,0,0,0}; // values for each digit


/// Configure C51 Timer0 for display work:
/// use 16bit timer, timer 0 overflow interrupt enabled
void Init_Timer0(void);

/// Initialize display work
void InitLEDSSD(void);

/// Set number to show on display on Right LSB 4 bits
void Display_LSB(unsigned int number);

/// Set number to show on display on Left MSB 4 bits
void Display_MSB(unsigned int number);

/// Set number to show on whole 8 digits of display
void Display_All(unsigned long number);

#endif // _SSD_DISPLAY__H_