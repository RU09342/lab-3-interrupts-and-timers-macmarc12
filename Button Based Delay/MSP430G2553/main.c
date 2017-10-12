#include <msp430.h>
#include <msp430g2553.h>

unsigned int x;
unsigned int y = 0x00;
unsigned int z = 1;
unsigned int count = 0;

void timerstart(int f);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // stop watchdog timer

    P1DIR |= BIT0;      // P1.0 as output
    P1OUT &= ~BIT0;     // clear LED

    P1DIR &=~(BIT3);    //set P1.3 as input
    P1REN|=BIT3;    //enable pull-up resistor
    P1OUT|=BIT3;
    P1IE |=BIT3;    //enable interrupt on P1.3
    P1IES |=BIT3;
    P1IFG &=~(BIT3);    //clear flag

    timerstart(20);       //set timer to 10Hz

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE);      // enable interrupts
}

void timerstart(int f)
{
    int n;
    TA0CCTL0 = CCIE;    //Enable interrupt
    TA0CTL = TASSEL_2 + MC_1 + ID_2;    //SMCLK
    n = 250000 / f;
    TA0CCR0 = n;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER_A(void)
{
    if (y != 0)
    {
        if (P1IN & BIT3)
        {
            x = 0;
            y = 0;
            count = 0;
        }

        else
        {
            P1OUT |= BIT0;
            z++;
        }
    }

    else
    {
        if (count == z)
        {
            P1OUT ^= 0x01;  //Toggle LED
            count = 0;   // reset count
        }

        else
            count++;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    y = 1;
    z = 0;  //reset counter
    x = 1;
    __delay_cycles(50000);  //prevent bouncing
    P1IFG &=~(BIT3);     //clear flag
}
