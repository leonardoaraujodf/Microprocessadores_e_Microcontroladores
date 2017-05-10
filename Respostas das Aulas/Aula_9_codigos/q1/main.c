
#include <msp430g2553.h>

int deboucing (void)
{
    volatile int i;
    int comparacao;
    /*
    Tempo do contador
    
    300000 --------- 0,5 s
    x      ---------  0,050 s
    */

    for(i=0;i<3000;i++);
    {
      if(i==0)
      {
        comparacao = P1IN;
      }
      else if (comparacao =! P1IN)
      {
        comparacao = P1IN;
        i=0; /*reinicia a contagem*/
      }
    }
    return P1IN;
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
                 /*Inicializar as saídas em zero*/
  P1DIR = 0xFF; /*P1DIR = 11111111*/ 
                       
               
  P1OUT = 0x00;
                               
  //volatile int i;
  for(;;)
  {    
      P1OUT^=0x41; // PIOUT = 01000001 
      for(i=0;i<0x6000;i++);
  }

}