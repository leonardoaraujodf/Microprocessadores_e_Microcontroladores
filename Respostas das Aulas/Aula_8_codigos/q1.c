##include <msp430g2553.h>
volatile int i;
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
                 /*Inicializar as sa�das em zero*/
  P1DIR = 0x41; /* PIDIR - Quando em 0 � entrada - Quando em 1 � sa�da
                   PIDIR = 01000001      
                */
  P1OUT = 0x00;
                               
  //volatile int i;
  for(;;)
  {    
      P1OUT^=0x41; // PIOUT = 01000001 
      for(i=0;i<0x6000;i++);
  }

}

