#include<msp430.h>
#include<msp430g2553.h>

#define LED0 BIT0
#define LEDDIR P1DIR
#define LEDOUT P1OUT

int main(void)
{

    WDTCTL = WDTPW + WDTHOLD;    // Disable Watchdog Timer
    LEDDIR |= LED0;     // Set LED to output
    CCTL0 = CCIE;       //Interrupt enabled
    TACTL = TASSEL_2 + MC_2;   //Continuous mode

    __enable_interrupt();
}

#pragma vector=TIMER0_A0_VECTOR    //Interrupt
__interrupt void Timer_A (void)
{
  LEDOUT ^= LED0;    // Flip LED
}
