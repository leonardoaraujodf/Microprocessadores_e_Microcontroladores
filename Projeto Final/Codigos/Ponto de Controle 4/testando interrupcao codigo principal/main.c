#include<msp430g2553.h>
#define BTN BIT3
#define INPUT1 BIT2 //INPUT FROM IC L293B
#define INPUT2 BIT4 //INPUT FROM IC L293B
#define INPUT3 BIT5 //INPUT FROM IC L293B
#define INPUT4 BIT7 //INPUT FROM IC L293B
#define INPUTS (INPUT1 + INPUT2 + INPUT3 + INPUT4)
#define ADC_CHANNELS 2
volatile unsigned int com=0;
volatile unsigned int impulse=0;
volatile unsigned int stop=0;
unsigned int adc[ADC_CHANNELS]=0;

void Control_Speed(int Speed)
{
    if(Speed == 0)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 0;
      TACCTL1 = OUTMOD_7;
      TACTL = TASSEL_2 + ID_0 + MC_1;
    }
    else if(Speed == 1)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 2500; //25% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TASSEL_2 + ID_0 + MC_1;      
    }
    else if(Speed == 2)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 3000; //35% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TASSEL_2 + ID_0 + MC_1;      
    }
    else if(Speed == 3)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 3500; //45% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TASSEL_2 + ID_0 + MC_1;
      
    }
    else if(Speed == 4)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 4000; //55% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TASSEL_2 + ID_0 + MC_1;
    }
    else if(Speed == 5)
    {
      TACTL = TACLR;
      TACCR0 = 10000; //100 hz
      TACCR1 = 75000; //75% of the Duty Cycle
      TACCTL1 = OUTMOD_7;
      TACTL = TASSEL_2 + ID_0 + MC_1;
    }
}

extern int Motor_Direction(char c1,char c2);
void Change_Direction(void)
{
  //adc[0] = p1.1 - sensor esquerda
  //adc[1] = p1.0 - sensor direita
  volatile unsigned int i = 2000;
  if((adc[0] > 800) && (adc[1] > 800))
  {
    P1OUT &= ~INPUTS;
    P1OUT |= 0x84;
    if((impulse==0) && (com!=0))
    {
    volatile unsigned int delay = 8000;
    Control_Speed(5);
    while(delay--);
    Control_Speed(com);
    impulse++;
    } 
  }
  else if((adc[1] < 800) && (adc[0] > 800))
  {
    //right motor stops
    P1OUT &= ~INPUTS;
    P1OUT |= 0x94; //Motor_Direction('S','R');
    impulse=0;
  }
  else if((adc[0] < 800) && (adc[1] > 800))
  {
    //left motor stops
    P1OUT &= ~INPUTS;
    P1OUT |= 0xA4; //Motor_Direction('R','S');
    impulse=0;
  }
  else
  {
    if(stop==1)
    {
    P1OUT &= ~INPUTS;
    P1OUT |= 0xB4; //Motor_Direction('S','S');
    stop=0;
    }
    else
    {
      stop=1;
      volatile unsigned int delay = 1000;
      while(delay--);
    }
    impulse=0;
  }
  while(i--);
}

void Setup_ADC(void)
{
  ADC10CTL0 |=  SREF_0 +  ADC10SHT_0 + MSC + ADC10ON + ADC10IE; //Reference from 
  //Vcc and Vss, sampling time of 16×ADC10CLKs, ADC10ON
  ADC10CTL1 |= INCH_1 + CONSEQ_1 + ADC10SSEL_3 + SHS_0; //Input channel A1 and A0; repeated sequence 
  ADC10AE0 = BIT0 + BIT1; // Analog Input in P1.0 and P1.1; 
  ADC10DTC1 = ADC_CHANNELS; // 2 conversions
  ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
}

void Read_ADC(void)
{
  ADC10CTL0 &= ~ENC;
  while (ADC10CTL1 & BUSY);// Wait if ADC10 core is active
  ADC10SA = (unsigned int)adc;// Copies data in ADC10SA to unsigned int adc array
  ADC10CTL0 |= ENC + ADC10SC;
  __bis_SR_register(CPUOFF + GIE);
  Change_Direction();
}

void Setup_Button(void)
{
  P1DIR &= ~BTN;
  P1OUT |= BTN; /*Definindo o resistor de pull-up e pull-down*/
  P1REN |= BTN; //Definindo como pull-down
  P1IE |= BTN; // Habilita Interrupcao na porta P1.0
  P1IES |= BTN; //Habilita Interrupcao na borda de descida
}

void Setup_PWM(void)
{
  P1DIR |= BIT6;
  P1SEL |= BIT6; //Usando a funcao TA0.1 na porta P1.6
  P1SEL2 &= ~BIT6;//Usando a funcao TA0.1 na porta P1.6
}

void Setup_L293B(void)
{
  P1OUT &= ~INPUTS;/*Inicializando as saidas em 0*/
  P1DIR |= INPUTS; 
}

void Read_Button(void)
{
    volatile unsigned int i = 20000;
    //Controle de Velocidade dos Motores
    if((P1IN&BTN)==0)
    {
      if(com!=4)
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
      BIT0        |         SENSOR 1 (ENTRADA)
      BIT1        |         SENSOR 2 (ENTRADA)
      BIT2        |         INPUT 1 (L293B) - SAIDA
      BIT3        |         BOTÃO DE CONTROLE DE VELOCIDADE (ENTRADA)
      BIT4        |         INPUT 2 (L293B) - SAIDA
      BIT5        |         INPUT 3 (L293B) - SAIDA
      BIT6        |         ENABLE1 e ENABLE2 (L293B) - SAIDA PWM
      BIT7        |         INPUT 4 (L293B) - SAIDA               

===========Vista superior do robo============================

                sensor 2       sensor 1
                  -X-            -X-    
          |------------------------------|
     |----| ----------         ----------|----|   
     |    | |  motor 2|        | motor 1||    |
     |    | |---------|        |---------|    |
     |----|                              |----|
          |------------------------------|
  */


int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
  DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
  Setup_L293B();
  Setup_Button();
  Setup_PWM();
  Setup_ADC();
  Read_ADC();
  Control_Speed(0); //Inicializar os motores parados 
  while(1)
  {
    Read_Button();
    Read_ADC();
    //__bis_SR_register(CPUOFF + GIE);
  }
}

//P1IN interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{   
    P1IFG &=~BTN;  
    __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}