
#include <stdint.h>
#include "gpio.h"
#define UART ((NRF_UART_REG*)0x40002000)

typedef struct{
	volatile uint32_t ENABLE;
	volatile uint32_t BAUDRATE;
	volatile uint32_t TXD;
	volatile uint32_t RXD;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELRXD;
	volatile uint32_t PIN_CNF[32];
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELCTS;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t TXDRDY;
	volatile uint32_t RXDRDY;
} NRF_UART_REG;



void uart_init(){
	UART->ENABLE = 4;
	GPIO->PIN_CNF[24] = 1;  // TXD
	GPIO->PIN_CNF[25] = 0;  // RXD
	UART->PSELTXD = 24;
	UART->PSELRXD = 25;
	UART->PSELRTS = 0xFFFFFFF;
	UART->PSELCTS = 0xFFFFFFF;
	UART->BAUDRATE = 0x00275000;
	UART->STARTRX =1;
};


void uart_send(char letter){
	UART->STARTTX=1;
	UART->TXDRDY=0;
	UART->TXD = letter;
	while(!(UART->TXDRDY));		
	UART->STOPTX = 1;
};


char uart_read(){
	char letter;
	UART->RXDRDY = 0;
	while(!(UART->RXDRDY));	
	letter = UART->RXD;
	if(letter){return letter;
	}

	else{ return '\0';};	

};

