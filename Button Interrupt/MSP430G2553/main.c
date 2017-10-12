#include <msp430.h> 

int x=0;
void main(void)
{

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1DIR |= (BIT0 + BIT6); // Set LEDS as outputs
    P1OUT &= ~(BIT0 + BIT6);
    P1REN |= BIT3;
    P1OUT |= BIT3; //Set resistor as pull-up.
    P1IES |= BIT3;

    P1IE |= BIT3; //Sets mask

    __enable_interrupt();

    while (1)
    {

        if(x>0)
        {
            P1OUT ^= (BIT0 + BIT6);
            __delay_cycles(100000);
        }
    }
}

#pragma vector=PORT1_VECTOR //interrupt
__interrupt void Port_1(void)
{
    x ^= 0x01;  // flips LED
    P1IFG &= ~BIT3; // Clear flag
    P1OUT &= ~(BIT0 + BIT6);

}
