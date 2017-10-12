# Button Interrupt
The objective of this section is to get us familiar with using interrupts over polling, as it is much more of a time saver.
This is done in conjunction with a button for ease of access. Doing it in this method not only saves the processor more time, it also gives you more access to the LED timers.

## Getting Started
We will develop code that causes the press of a button to create an interrupt in the code, halting it until the button is released, and giving it new directions in the meantime, like lighting the LED.
```c
__enable_interrupt();
```
This is the line that enables the interrupt.
```c
#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
```
And this is the start of the interrupt function.

### Acknowledgement
I had some trouble with this section so I used the resources of the internet and classmates to help fill in holes I had in my knowledge and code.