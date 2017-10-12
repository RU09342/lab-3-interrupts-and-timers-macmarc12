# TIMER A Blink
The objective of this section is to get us more familiar with timers. There are different types of timers, including: up, up/down, and continuous, each of which function a little differently.

## Getting Started
We can use timers to control the speed at which our LEDs blink.
```c
timerstart(10);
```
This line sets the timer frequency.

```c
void timerstart(int f)
{
```
And this line begins the timer function.

### Acknowledgement
I had some trouble with this section so I used the resources of the internet and classmates to help fill in holes I had in my knowledge and code.