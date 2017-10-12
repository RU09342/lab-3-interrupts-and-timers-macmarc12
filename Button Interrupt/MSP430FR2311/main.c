#include <msp430.h> 

int x=0;
void main(void)
{

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1DIR |= (BIT0); // Set LED as outputs
    P1OUT &= ~(BIT0);
    P1REN |= BIT1;
    P1OUT |= BIT1; //Set resistor as pull-up.
    P1IES |= BIT1;

    P1IE |= BIT1; //Sets mask

    PM5CTL0 &= ~LOCKLPM5;     // Disable the GPIO power-on default high-impedance mode

    __enable_interrupt();

    while (1)
    {

          if(x > 0)
           {
              P1OUT ^= (BIT0);
              __delay_cycles(100000);
           }
    }
}

#pragma vector=PORT1_VECTOR //interrupt
__interrupt void Port_1(void)
{
    x ^= 0x01;  // flips LED
    P1IFG &= ~BIT1; // Clear flag
    P1OUT &= ~(BIT0);
}
