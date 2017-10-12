#include <msp430.h> 

int x=0;
void main(void)
{

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1DIR |= (BIT0); // Set LEDS as outputs
    P1OUT &= ~(BIT0);
    P2REN |= BIT1;
    P2OUT |= BIT1; //Set resistor as pull-up.
    P2IES |= BIT1;

    P2IE |= BIT1; //Sets mask

    PM5CTL0 &= ~LOCKLPM5;     // Disable the GPIO power-on default high-impedance mode

    __enable_interrupt();

    while (1)
    {

        if(x > 0)
        {
            P1OUT ^= (BIT0);
            __delay_cycles(75000);
        }
    }
}

#pragma vector=PORT2_VECTOR //interrupt
__interrupt void Port_2(void)
{
       x ^= 0x01;  // flips LED
       P2IFG &= ~BIT1; // Clear flag
       P1OUT &= ~(BIT0);
}
