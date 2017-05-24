#include <msp430g2553.h>

int Deboucing(int porta)
{
  /*A função recebe qual porta deve realizar o deboucing e retorna o valor lido da porta P1.X 
  onde X refere-se a porta escolhida*/
  /*Supondo que a porta P1 já está definida.*/
  
  x = P1IN;
  x &= porta;
  for(i=0;i<5000;i++)
  {
    if((P1IN&porta) != x))
      {
        i = 0; //Houve variação na entrada, deve-se reiniciar a contagem;
      }
  }
  return x;
}
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  return 0;
}

