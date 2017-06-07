#include<msp430g2553.h>
volatile unsigned int i=3;
#define BTN BIT3
/*Os sensores de detecção de linha estarão nos bits 6 e 7 de P1IN*/

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
  if (string1 == "Right" && string2 == "Right")
  {
    /*P1OUT = 00010100*/
    return  0x14;
  }
  else if (string1 == "Right" && string2 == "Left")
  {
    /*P1OUT = 00100100*/
    return  0x24;
  }
  else if (string1 == "Left" && string2 == "Left")
  {
    /*P1OUT = 00101000*/
    return  0x28;
  }
  
  else if (string1 == "Left" && string2 == "Right")
  {
    /*P1OUT = 00011000*/
    return  0x18;
  }
}

int Detectar_Sensor(void)
{
  /* BIT EM P1OUT    |     PORTA DO L293B 
         BIT6        |         SENSOR 1
         BIT7        |         SENSOR 2
  
  */
  P1DIR |= 0x3F; 
  if(analogRead(A6) > 512)
  /*Se detectarmos uma linha no sensor1, deve-se virar a esquerda*/
  {
    return Motor_Direction("Left","Right"); //vire a esquerda
  }
  else if(analogRead(A7) > 512)
  {
  /*Se detectarmos uma linha no sensor2, deve-se virar a direita*/
    return Motor_Direction("Right","Left"); //vire a direta
  }
  else
  {
    return Motor_Direction("Right","Right"); //siga reto
  }
}

void Controle_Velocidade(void)
{
  P1DIR &= ~(BTN); // 00001000, 0 - entrada, 1 - saida
  P1REN |= BTN; // setar o resistor da porta
  P1OUT |= BTN; // resistor de pull-up no bit 3

  if((P1IN & BTN) == 0)
  {
    i++;
    if(i==5)
    {
      i=0;
    }
    delay(500);
  }
  
  if(i == 0)
  {
    analogWrite(0,0);
    analogWrite(1,0);
  }
  else if(i == 1)
  {
    analogWrite(0,64);
    analogWrite(1,64);    
  }
  else if(i == 2)
  {
    analogWrite(0,127);
    analogWrite(1,127);
  }
  else if(i == 3)
  {
    analogWrite(0,191);
    analogWrite(1,191);
  }
  else if(i == 4)
  {
    analogWrite(0,255);
    analogWrite(1,255);
  } 
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT = 0;
  P1DIR |= 0x3F; /*P1DIR = 00111111*/
  for(;;)
  {
    Controle_Velocidade();
    P1OUT |= Detectar_Sensor(); 
    
  }
  
}
