#include <msp430g2553.h> 

/*
 * main.c
 */

void Atraso(volatile unsigned int x)
{
    TACCR0 = 1000-1; //capture mode ativo para pegar o timer em 999
    TACTL |= TACLR; // limpar o timer A
    TACTL = TASSEL_2 + ID_0 + MC_1; //TASSEL_2 escolhe SMCLK como o clock do TAR
                                    //ID_0 significa que o clock sera dividido por 1
                                    //MC_1 significa que o timer segue o modo UP e vai contar até o valor setado em TACCR0
    while(x>0)
    {
      x--;
      while((TACTL&TAIFG)==0);
              TACTL &= ~TAIFG;
    }
    TACTL = MC_0; //timer no modo stop

}

void serial_para_paralelo(void)
{
    /*Na entrada vem uma palavra da forma 1 XXXX XXXX 0
     *
     */
    if((P2IN&BIT0) == 1)
    {
        /*Deve ser verificado se o primeiro bit é 1.
         *É meio que a lógica do bit de paridade
         *
         */
        Atraso(1); /*Espera 1 ms pra aparecer a primeira entrada de dados*/
        int x=0,i,y=0;
            for(i=0;i<8;i++)
            {
                x = 0;
                x |= (P2IN&BIT0);//mascarando a porta P2IN para pegar somente o valor de P2.0 e armazenar em x
                y |= (x << i); //desloca x
                Atraso(1); //Espera 1 ms até vir a próxima entrada
            }
        if((P2IN&BIT0)==0)
            {/*Aqui tem que verificar outro bit na porta P2.0*/
             P1OUT = y;
            }
    }
}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT = 0; //Limpando a porta P1
    P1DIR = 0xFF; //Definindo toda a porta P1 como saida
    P2DIR &= ~(BIT0); //Definindo P2.O como entrada
    for(;;)
    {
        serial_para_paralelo();
    }
    return 0;
}
