#include<msp430g2553.h>

volatile unsigned int i;
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT = 0;
  P1DIR |= 0x41;
  for(;;)
  {
    P1OUT ^= 0x41;
    for(i=0;i<60000;i++);
    P1OUT ^= 0x41;
    for(i=0;i<30000;i++);   
  }
  
}

