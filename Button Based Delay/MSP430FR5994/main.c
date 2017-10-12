#include <msp430.h>
#include <msp430fr5994>

unsigned int x;
unsigned int y = 0x00;
unsigned int z = 1;
unsigned int count = 0;

void timerstart(int f);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;        // Disable the GPIO power-on default high-impedance mode

    P1DIR |= BIT0;  // P1.0 as output
    P1OUT &= ~BIT0;     // clear LED

    P5DIR &=~(BIT6);    //set P5.6 as input
    P5REN|=BIT6;    //enable pull-up resistor
    P5OUT|=BIT6;
    P5IE |=BIT6;    //enable interrupt
    P5IES |=BIT6;
    P5IFG &=~(BIT6);  //clear flag

    timerstart(20);    //set timer to 10Hz

    __enable_interrupt();
}

void timerstart(int f)
{
    int n;
    TA0CCTL0 = CCIE; //Enable interrupt
    TA0CTL = TASSEL_2 + MC_1 + ID_2; //SMCLK
    n = 250000 / f;
    TA0CCR0 = n;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER_A(void)
{
    if (enabled != 0)
    {
        if (P5IN & BIT6)         //then reset both count and enabled when the button is released
        {
            x = 0; // state the button is no longer pressed
            y = 0; //reset our variables
            count = 0;
        }

        else
        {
            P1OUT |= BIT0; //hold LED on
            z++; //increment counter
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

#pragma vector=PORT5_VECTOR
__interrupt void PORT_5(void)
{
    y = 1;   //set when button is pressed and reset when released in the TIMERA interrupt
    z = 0;    //reset timing counter
    x = 1;    //state that the button is pressed
    __delay_cycles(100000);
    P5IFG &=~(BIT6);    //clear flag
}
