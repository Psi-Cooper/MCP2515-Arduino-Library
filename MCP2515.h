#ifndef MCP2515_h
#define MCP2515_h

#include <Arduino.h>
#include <SPI.h>

/*
Created by: Simon Cooper
University of Bath
Integrated Mechanical and Electrical Engineering Final Year Project
Designed to include the full functionality of the MCP2515 CAN controller
With references to the library produced by Kyle Crockett

Designed to be used with the CAN shield designed by Simon Cooper
using a 16MHz oscillator. (20MHz quartz crystal for >125Kh)
*/
#define RESET_PIN 2
#define INT_PIN 3

/*******************
	Register Map
*******************/

//Support bit modify SPI command
#define BFPCTRL 	0x0C		//RXnBF Control and Status
#define TXRTSCTRL 	0x0D		//TXnRTS PIN CONTROL AND STATUS REGISTER - Request to send bits for buffers
#define CANSTAT		0x0E		//CAN status register
#define CANCTRL		0x0F		//CAN control register - clock out and clock prescalers
#define CNF3		0x28		//Bit timing configuration register 3
#define CNF2		0x29		//Bit timing configuration register 2
#define CNF1		0x2A		//Bit timing configuration register 1
#define CANINTE		0x2B		//Interrupt enables
#define CANINTF		0x2C		//Interrupt flags
#define EFLG		0x2D		//Error flags
#define TXB0CTRL	0x30		//Transmit buffer 0 control register
#define TXB1CTRL	0x40		//Transmit buffer 1 control register
#define TXB2CTRL	0x50		//Transmit buffer 2 control register
#define RXB0CTRL	0x60		//Receive  buffer 0 control register
#define RXB1CTRL	0x70		//Receive  buffer 1 control register

/********************************
*	Mask and filter Registers   *
********************************/
//Note: Filter/mask ID registers- 4 registers for SIDH SIDL EID8 EID0 starting at SIDH

//Filters: 
//0,1 - RX buffer 0
//2,3,4,5 - RX buffer 1
#define FILTER0 	0x00		//Receive filter 0 standard ID high
#define FILTER1		0x04		//Receive filter 1 standard ID high
#define FILTER2		0x08		//Receive filter 2 standard ID high
#define FILTER3		0x10		//Receive filter 3 standard ID high
#define FILTER4		0x14		//Receive filter 4 standard ID high
#define FILTER5		0x18		//Receive filter 5 standard ID high

//Masks:
//0 - RX buffer 0
//1 - RX buffer 1
#define MASK0		0x20		//Receive mask 0 standard ID high
#define MASK1		0x24		//Receive mask 1 standard ID high

/********************************
*	TX and RX buffer Registers  *
********************************/
//Note: ID registers - 4 registers for SIDH SIDL EID8 EID0 starting at SIDH followed by DLC register and 8 data registers
#define TXB0SIDH	0x31		//Transfer buffer 0 standard ID high
#define TXB1SIDH	0x41		//Transfer buffer 1 standard ID high
#define TXB2SIDH	0x51		//Transfer buffer 2 standard ID high
#define RXB0SIDH	0x61		//Receive  buffer 0 standard ID high
#define RXB1SIDH	0x71		//Receive  buffer 1 standard ID high
#define TXB0DLC		0x35		//Transfer buffer 0 data length code
#define TXB1DLC		0x45		//Transfer buffer 1 data length code
#define TXB2DLC		0x55		//Transfer buffer 2 data length code
#define RXB0DLC		0x65		//Receive  buffer 0 data length code
#define RXB1DLC		0x75		//Receive  buffer 1 data length code

/*******************
	SPI Commands
*******************/
#define RESET		0xC0		// Resets internal registers and sets configuration mode
#define READ		0x03		// Read data from register beginning at selected address
#define WRITE		0x02		// Write data to  register beginning at selected address
#define READSTATUS  0xA0		// Reads several status bits for TX and RX functions
#define RXSTATUS 	0xB0		// Indicates filter match and message type (standard/extended/remote) of received message
#define BITMODIFY	0x05		// Allows modifying of individual bits in supporting registers: instruction - address - mask - data

#define READRX0ID	0x90		// Read from RXB0SIDH (Note: associate RX flag bit is cleared after CS goes high) 	
#define READRX0D0	0x92		// Read from RXB0D0 (first data byte)
#define READRX1ID	0x94		// Read from RXB1SIDH
#define READRX1D0	0x96		// Read from RXB1D0

#define LOADTX0ID	0x40		// Load from TXB0SIDH
#define LOADTX0D0	0x41		// Load from TXB0D0
#define LOADTX1ID	0x42		// Load from TXB1SIDH
#define LOADTX1D0	0x43		// Load from TXB1D0
#define LOADTX2ID	0x44		// Load from TXB2SIDH
#define LOADTX2D0	0x45		// Load from TXB2D0

#define RTSTXB0		0x81		// Request to send TX buffer 0
#define RTSTXB1		0x82		// Request to send TX buffer 1
#define RTSTXB2		0x84		// Request to send TX buffer 2 		- Incorrect in previous library

/**********************
	Baud Rate Config
**********************/
/***
Baud rate configurations. Bit time has to be between 8 and 25 TQ. Old library used 16TQ to achieve this. Will need to alter the following
values for 20MHz resonator when I get.
***/	

// Configured for 16MHz oscillator
// SOF = 0
// SAM = 0
// WAKFIL = 0
// 5 kbps - added
#define CNF1_5 		0x3F
#define CNF2_5 		0xBF
#define CNF3_5 		0x07
// 10 kbps
#define CNF1_10 	0x31
#define CNF2_10		0xB8
#define CNF3_10		0x05
// 20 kbps
#define CNF1_20 	0x18
#define CNF2_20		0xB8
#define CNF3_20		0x05
// 50 kbps
#define CNF1_50 	0x09
#define CNF2_50		0xB8
#define CNF3_50		0x05
// 100 kbps
#define CNF1_100 	0x04
#define CNF2_100	0xB8
#define CNF3_100	0x05
// 125 kbps
#define CNF1_125 	0x03
#define CNF2_125	0xB8
#define CNF3_125	0x05
// 250 kbps
#define CNF1_250 	0x01
#define CNF2_250	0xB8
#define CNF3_250	0x05
// 500 kbps
#define CNF1_500 	0x00
#define CNF2_500	0xB8
#define CNF3_500	0x05

// 800 kbps - added
// Cannot be supported

// 1000 kbps - Bit time = 8TQ
#define CNF1_1000 	0x80 //SJQ = 3TQ BRP = 0
#define CNF2_1000	0x90 //
#define CNF3_1000	0x02


enum MCP2515Mode {CONFIGURATION, NORMAL, LISTEN, SLEEP, LOOPBACK};
enum messageType {STANDARD, EXTENDED, STANDARDREMOTE, EXTENDEDREMOTE};
//enum transmitPriority {HIGHEST, HIGH, LOW, LOWEST};

class MCP2515
{
private:
	int _ss;	// spi slave select pin
	int _reset;	// reset pin if connected (reset can be controlled over SPI instead)
	// could need other pins here, ie interrupts and TX and RX interrupts
public:
	MCP2515(int ss); //input slave select pin - allows multiple buses
	//MPC2515();

	//NEED TO INCLUDE ALL FUNCTIONS FROM HERE
	//START WITH MODE SET AND RESET FUNCTIONS

	void begin();	//set up controller
	
	void setBitRate(int bitRate);
	//void setMode(MCP2515Mode mode);
	int setMode(MCP2515Mode mode);
	
	
	void loadTXBuffer(uint32_t ID, byte command, messageType frameType, int DLC, byte dataBytes[]);
	void loadTXBuffer0(uint32_t ID, messageType frameType, int dataLength, byte dataBytes[]);
	void loadTXBuffer1(uint32_t ID, messageType frameType, int dataLength, byte dataBytes[]);
	void loadTXBuffer2(uint32_t ID, messageType frameType, int dataLength, byte dataBytes[]);

	void sendTXBuffer0();
	void sendTXBuffer1();
	void sendTXBuffer2();
	void sendTXBuffer(byte RTSCOMMAND);


	void readRXBuffer(byte command, byte *DLC, byte *data, uint32_t* ID, byte* ext, byte* remote);
	void readRXBuffer0(byte *DLC, byte *data, uint32_t *ID, byte* ext, byte* remote);
	void readRXBuffer1(byte *DLC, byte *data, uint32_t *ID, byte* ext, byte* remote);

	byte RXStatus();
	void reset();	//reset controller - perform on startup
	byte read(byte address);
	void write(byte address, byte data);
	void multiWrite(byte address, byte IDBytes[], byte dataBytes[], int DLC);
	void modify(byte address, byte mask, byte data);
};

#endif