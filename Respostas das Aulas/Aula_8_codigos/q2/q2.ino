#include<msp430g2553.h>

int Motor_Direction(char string[])
{
  /*
  Forma de programação para o CI L293B
         CHIP ENABLE 1   -|------- |-
                        -|        |-
            -|        |-
            -|  L293B |-
            -|        |-
            -|        |-
            -|        |-         
            -|________|-
  BIT0 - ENABLE1
  
  */
  if (string == "Right")
  {
    return  0x
  }
  
}

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
