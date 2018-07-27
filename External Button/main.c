#include <msp430.h> 

/*
 * main.c
 */

int direction=0;

int power (int num, int p){
	int i=0,res=1;
	for(i=0;i<p;i++){
		res=res*num;
	}
	return res;
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR |= (BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7);
	P2DIR |= BIT0;
	P1DIR &= ~BIT3;

	P1REN = 0;//because of external button usage we disabled internal resistor

	P1IE |= BIT3;
	P1IES |= BIT3;

	P1IFG &= ~BIT3;

	__enable_interrupt();
	
	return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){

		P2OUT &= ~BIT0;
		direction=direction+1;
		int i=0;
		if(direction %2 != 0){
			for(i=0;i<8;i++){
				if(i != 3){
					P1OUT |= power(2,i);
					__delay_cycles(500000);
					P1OUT = BIT3;
				}
			}
			P2OUT |= BIT0;
			__delay_cycles(500000);
			P2OUT &= ~BIT0;
		}

		else{
			P2OUT |= BIT0;
			__delay_cycles(500000);
			P2OUT &= ~BIT0;
			for(i=7;i>=0;i--){
				if(i != 3){
					P1OUT |= power(2,i);
					__delay_cycles(500000);
					P1OUT = BIT3;
				}
			}
		}
		P1IFG &= ~BIT3;
}

