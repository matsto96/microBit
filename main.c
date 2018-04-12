#include <stdint.h>
#include "uart.h"
#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;  // A
	GPIO->PIN_CNF[26] = 0;  // B

	int sleep = 0;
	
	while(1){
		if(!(GPIO->IN & (1<<17))){
			uart_send('A');}
			/*for(int i = 4; i < 12; i++){ 
				GPIO->OUTSET = (1 << i);}
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);}}*/
		if(!(GPIO->IN & (1<<26))){
			uart_send('B');}
			/*for(int i = 4; i < 12; i++){ 
				GPIO->OUTCLR = (1 << i);}
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);}}*/

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
