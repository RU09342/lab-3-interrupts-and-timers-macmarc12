#include <msp430.h> 

int x=0;
void main(void)
{

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1DIR |= (BIT0 + BIT1); // Set LEDS as outputs
    P1OUT &= ~(BIT0 + BIT1);
    P5REN |= BIT6;
    P5OUT |= BIT6; //Set resistor as pull-up
    P5IES |= BIT6;

    P5IE |= BIT6; //Set mask

    PM5CTL0 &= ~LOCKLPM5;     // Disable the GPIO power-on default high-impedance mode

    __enable_interrupt(); // enables interrupt for board

    while (1)
    {

        if(x > 0)
        {
            P1OUT ^= (BIT0 + BIT1);
            __delay_cycles(80000);
        }
    }
}

#pragma vector=PORT5_VECTOR //interrupt
__interrupt void Port_5(void)
{
    x ^= 0x01; //flips LED
    P5IFG &= ~BIT6; //Clear flag
    P1OUT &= ~(BIT0 + BIT1);
}
