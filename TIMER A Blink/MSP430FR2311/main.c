#include<msp430.h>
#include<msp430fr2311.h>

#define LED0 BIT0
#define LEDDIR P1DIR
#define LEDOUT P1OUT

int main(void)
{

    PM5CTL0 &= ~LOCKLPM5;

    WDTCTL = WDTPW + WDTHOLD;    // Disable Watchdog Timer
    LEDDIR |= LED0;      // Set the LED to an output
    TB0CCTL0 = CCIE;     // CCR0 interrupt enabled
    TBCTL = TBSSEL_2 + MC_2;  //Continuous mode

    __enable_interrupt();
}

#pragma vector=TIMER0_B0_VECTOR //Interrupt
__interrupt void Timer_B (void)
{
  LEDOUT ^= LED0;  // Flip LED
}
