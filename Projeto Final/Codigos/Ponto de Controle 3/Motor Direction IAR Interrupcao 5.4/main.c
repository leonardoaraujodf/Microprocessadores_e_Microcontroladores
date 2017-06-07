#include<msp430g2553.h>
#define BTN BIT3
volatile unsigned int com=0;

void Control_Speed(int Speed)
{
    if(Speed == 0)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 0;
      TACCTL1 = OUTMOD_7;
      TACTL = TACTL = TASSEL_2 + ID_0 + MC_1;
    }
    else if(Speed == 1)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 5000; //50% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TACTL = TASSEL_2 + ID_0 + MC_1;      
    }
    else if(Speed == 2)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 6250; //62.5% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TACTL = TASSEL_2 + ID_0 + MC_1;      
    }
    else if(Speed == 3)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 7500; //75% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TACTL = TASSEL_2 + ID_0 + MC_1;
      
    }
    else if(Speed == 4)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 8750; //87.5% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TACTL = TASSEL_2 + ID_0 + MC_1;
    }
    else if(Speed == 5)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 10000; //100% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TACTL = TASSEL_2 + ID_0 + MC_1;
    }
}

extern int Motor_Direction(char c1,char c2);

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
  BIT EM P1OUT    |  SIGNIFICADO DA ENTRADA/SAIDA CORRESPONDENTE        
      BIT0        |         INPUT 1 (L293B) (SAIDA)
      BIT1        |         INPUT 2 (L293B) (SAIDA)
      BIT2        |         INPUT 3 (L293B) (SAIDA)
      BIT3        |         BOTÃO DE CONTROLE DE VELOCIDADE (ENTRADA)
      BIT4        |         INPUT 4 (L293B)  (SAIDA)
      BIT5        |         SENSOR 1 (ENTRADA)
      BIT6        |         ENABLE1 e ENABLE2 (L293B) - SAIDA PWM
      BIT7        |         SENSOR 2 (ENTRADA)

===========Vista superior do robo============================

                sensor 1       sensor 2
                  -X-            -X-    
          |------------------------------|
     |----| ----------         ----------|----|   
     |    | |  motor 1|        | motor 2||    |
     |    | |---------|        |---------|    |
     |----|                              |----|
          |------------------------------|
  */

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
  DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
  P1OUT = 0;/*Inicializando as saidas em 0*/
  P1DIR |= 0x57; /*P1DIR = 01010111*/
  P1DIR &= ~BTN;
  P1OUT |= BTN; /*Definindo o resistor de pull-up e pull-down*/
  P1REN |= BTN; //Definindo como pull-down
  P1SEL |= BIT6; //Usando a funcao TA0.1 na porta P1.6
  P1SEL2 &= ~BIT6;//Usando a funcao TA0.1 na porta P1.6
  P1IES |= BTN; //Habilita Interrupcao na borda de descida
  P1IE |= BTN; // Habilita Interrupcao na porta P1.0
  Control_Speed(0); //Inicializar os motores parados
  P1OUT |= Motor_Direction('R','R'); // Motores girando para a direita
  _BIS_SR(GIE + LPM0_bits); 
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
  
    volatile unsigned int i = 60000;

    //Controle de Velocidade dos Motores
    if((P1IN&BTN)==0)
    {
      if(com!=5)
      {
        com++;
        Control_Speed(com);
        while(i--);
      }
      else
      {
        com = 0;
        Control_Speed(0);
        while(i--);
      }
    }
}

