#include <msp430.h>
#include <msp430f5529.h>

unsigned int x;
unsigned int y = 0x00;
unsigned int z = 1;
unsigned int count = 0;

void timerstart(int f);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;   // P1.0 as output
    P1OUT &= ~BIT0;     // clear LED

    P1DIR &=~(BIT1); //set P1.1 as input
    P1REN|=BIT1;    //enable pull-up resistor
    P1OUT|=BIT1;
    P1IE |=BIT1;    //enable interrupt for P1.1
    P1IES |=BIT1;
    P1IFG &=~(BIT1);    //clear flag

    timerstart(20);    //set timer to 10Hz

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE); // enable interrupts
}

void timerstart(int f) // call function
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
        if (P1IN & BIT1)
        {
            x = 0;
            y = 0;
            count = 0;
        }

        else
        {
            P1OUT |= BIT0;
            z++; //increment
        }
    }

    else
    {
        if (count == z)
        {
            P1OUT ^= 0x01; //Toggle LED
            count = 0;  // reset count
        }

        else
            count++;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    y = 1;
    z = 0;         //reset counter
    x = 1;
    __delay_cycles(100000);     // prevent bouncing
    P1IFG &=~(BIT1);    //clear flag
}
