#include <msp430.h>
#include <msp430fr6989.h>

volatile unsigned int x = 1;
void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |=BIT0; //set P1.0 as output
    P1DIR &=~(BIT1); //set P1.1 as input
    P1REN|=BIT1;//enable pull-up resistor
    P1OUT|=BIT1;
    P1IE |=BIT1;
    P1IES |=BIT1;
    P1IFG &=~(BIT1);//clear flag

    __enable_interrupt();

       while(1)
        {
            if (x > 0)
            {
                P1OUT ^= BIT0;
                switch(x) //Toggle LED speed
                {
                    case 1: __delay_cycles(200000);
                    case 2: __delay_cycles(100000);
                    case 3: __delay_cycles(50000);
                }
            }
                else
                    P1OUT &= ~BIT0;
        }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    if (x != 3)
        x++;
    else
        x = 0;
    while(P1IN & BIT1) {}
    __delay_cycles(50000); //Avoid bouncing
    P1IFG &=~(BIT1);    //clear flag
}
