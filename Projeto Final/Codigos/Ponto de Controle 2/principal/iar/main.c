#include<msp430g2553.h>
#define SENSOR1 BIT6
#define SENSOR2 BIT7
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

int Detectar_Sensor(void)
{
  if((P1IN & SENSOR1) == 0)
  /*Se detectarmos uma linha no sensor1, deve-se virar a esquerda*/
  {
    return Motor_Direction("Left","Right"); //vire a esquerda
  }
  else if((P1IN & SENSOR2) == 0)
  {
  /*Se detectarmos uma linha no sensor2, deve-se virar a direita*/
    return Motor_Direction("Right","Left"); //vire a direta
  }
  else
  {
    return Motor_Direction("Right","Right"); //siga reto
  }
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT = 0;
  P1DIR |= 0x3F; /*P1DIR = 00111111*/
  for(;;)
  {
    P1OUT = Detectar_Sensor(); 
  }
  
}