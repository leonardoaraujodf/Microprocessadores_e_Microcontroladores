#include<msp430g2553.h>

int Motor_Direction(char string1[],char string2[])
{
  /*
  Forma de programação para o CI L293B
  
         (1)CHIP ENABLE 1   -|------- |-  Vss (16)
         (2)INPUT 1         -|        |-  INPUT 4 (15)
         (3)OUTPUT 1        -|   CI   |-  OUTPUT 4 (14)
         (4)GND             -|  L293B |-  GND (13)
         (5)GND             -|        |-  GND (12)
         (6)OUTPUT 2        -|        |-  OUTPUT 3 (11)
         (7)INPUT 2         -|        |-  INPUT 3 (10)         
         (8)Vs              -|________|-  CHIP ENABLE 2 (9)
---------------------------------------------------------------  
  BIT EM P1OUT    |     PORTA DO L293B     
      BIT0        |         ENABLE 1
      BIT1        |         ENABLE 2
      BIT2        |         INPUT 1 (refere-se ao primeiro motor)
      BIT3        |         INPUT 2 (refere-se ao primeiro motor)
      BIT4        |         INPUT 3 (refere-se ao segundo motor)  
      BIT5        |         INPUT 4 (refere-se ao segundo motor)                   
  */
  if (string1 == "Right" && string2 == "Right")
  {
    /*P1OUT = 00010111*/
    return  0x17;
  }
  else if (string1 == "Right" && string2 == "Left")
  {
    /*P1OUT = 00100111*/
    return  0x27;
  }
  else if (string1 == "Left" && string2 == "Left")
  {
    /*P1OUT = 00101011*/
    return  0x2B;
  }
  
  else if (string1 == "Left" && string2 == "Right")
  {
    /*P1OUT = 00011011*/
    return  0x1B;
  }
}

volatile unsigned int i;
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT = 0;
  P1DIR |= 0x3F; /*P1DIR = 00111111*/
  for(;;)
  {
    P1OUT = Motor_Direction("Right","Left");  
  }
  
}