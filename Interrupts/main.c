#include <msp430.h> 

/*
 * main.c
 */

void yak_sondur(){

	P1OUT |= BIT6;

	__delay_cycles(1000000);

	P1OUT &= ~BIT6;

	__delay_cycles(1000000);
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR |= (BIT0 | BIT6);
	P1DIR &= ~BIT3;

	P1REN |= BIT3;
	P1OUT |= BIT3;
	
	P1IE |= BIT3;
	P1IES |= BIT3;

	P1IFG &= ~BIT3;

	_BIS_SR(GIE);

	while(1){
		yak_sondur();
	}

	return 0;
}
#pragma vector = PORT1_VECTOR
__interrupt void port_1(void){

	P1OUT ^= BIT0;
	P1IFG &= ~BIT3;
}
