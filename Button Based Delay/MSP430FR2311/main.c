#include <msp430.h>
#include <msp430fr2311.h>

unsigned int x;
unsigned int y = 0x00;
unsigned int z = 1;
unsigned int count = 0;

void timerstart(int f);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;     // Disable the GPIO power-on default high-impedance mode

    P1DIR |= BIT0; // set P1.0 as output
    P1OUT &= ~BIT0; // clear LED

    P1DIR &=~(BIT1);    //set P1.1 as input
    P1REN|=BIT1;    //enable pull-up resistor
    P1OUT|=BIT1;
    P1IE |=BIT1;    //enable interrupt on P1.1
    P1IES |=BIT1;
    P1IFG &=~(BIT1);    //clear flag

    timerstart(20);    //set timer to 10Hz

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE); //enable interrupts
}

void timerstart(int f) // call function
{
    int n;
    TB0CCTL0 = CCIE;    //Enable interrupt
    TB0CTL = TBSSEL_2 + MC_1 + ID_2; //SMCLK
    n = 250000 / f;
    TB0CCR0 = n;
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER_B(void)
{
    if (y != 0)
    {
        if (P1IN & BIT1)
        {
            buttonPressed = 0;
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
            P1OUT ^= 0x01; //Toggle LED
            count = 0;
        }

        else
            count++;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    y = 1;
    z = 0;     //reset counter
    x = 1;
    __delay_cycles(50000);      // prevent bouncing
    P1IFG &=~(BIT1);    //clear interrupt flag
}
