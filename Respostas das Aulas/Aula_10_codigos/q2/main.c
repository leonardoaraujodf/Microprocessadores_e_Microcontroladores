#include <msp430.h> 
#define LEDA BIT0
#define LEDB BIT1
#define LEDC BIT2
#define LEDD BIT3
#define LEDE BIT4
#define LEDF BIT5
#define LEDG BIT6
#define CT1 BIT7 // CT1 - Catodo Comum do Display 1
#define CT2 BIT0 // CT2 - Catodo Comum do Display 2 - Vai no bit 0 da P2OUT
/*
 * main.c
 */

void EscreveDigito(volatile char dig)
{
    if(dig=='0')
    {
    //Digito 0
    //LEDA = 1, LEDB = 1, LEDC = 1, LEDD = 1, LEDE = 1, LEDF = 1 e LEDG = 0
    P1OUT |= LEDA + LEDB + LEDC + LEDD + LEDE + LEDF;
    }
    else if(dig=='1')
    {
    //Digito 1
    //LEDA = 0, LEDB = 1, LEDC = 1, LEDD = 0, LEDE = 0, LEDF = 0 E LEDG = 0
    P1OUT |= LEDB + LEDC;
    }
    else if(dig=='2')
    {
    //Digito 2
    //LEDA = 1, LEDB = 1, LEDC = 0, LEDD = 1, LEDE = 1, LEDF = 0 E LEDG = 1
    P1OUT |= LEDA + LEDB + LEDE + LEDG;
    }
    else if(dig=='3')
    {
    //Digito 3
    //LEDA = 1, LEDB = 1, LEDC = 1, LEDD = 1, LEDE = 0, LEDF = 0 E LEDG = 1
    P1OUT |= LEDA + LEDB + LEDC + LEDD + LEDG;
    }
    else if(dig=='4')
    {
    //Digito 4
    //LEDA = 0, LEDB = 1, LEDC = 1, LEDD = 0, LEDE = 0, LEDF = 1 E LEDG = 1
    P1OUT |= LEDB + LEDC + LEDG;
    }
    else if(dig=='5')
    {//LEDA = 0, LEDB = 0, LEDC = 0, LEDD = 0, LEDE = 0, LEDF = 0 E LEDG = 0
     //Digito 5
     //LEDA = 1, LEDB = 0, LEDC = 1, LEDD = 1, LEDE = 0, LEDF = 1 E LEDG = 1
     P1OUT |= LEDA + LEDC + LEDD + LEDF + LEDG;
    }
    else if(dig=='6')
    {//LEDA = 1, LEDB = 0, LEDC = 1, LEDD = 1, LEDE = 1, LEDF = 1 E LEDG = 1
     //Digito 6
     P1OUT |= LEDA + LEDC + LEDD + LEDE + LEDF + LEDG;
    }
    else if(dig=='7')
    {//LEDA = 1, LEDB = 1, LEDC = 1, LEDD = 0, LEDE = 0, LEDF = 0 E LEDG = 0
     P1OUT |= LEDA + LEDC + LEDC;
    }
    else if(dig=='8')
    {//LEDA = 1, LEDB = 1, LEDC = 1, LEDD = 1, LEDE = 1, LEDF = 1 E LEDG = 1
     P1OUT |= LEDA + LEDB + LEDC + LEDD + LEDE + LEDF + LEDG;
    }
    else if(dig=='9')
    {//LEDA = 1, LEDB = 1, LEDC = 1, LEDD = 1, LEDE = 0, LEDF = 1 E LEDG = 1
     P1OUT |= LEDA + LEDB + LEDC + LEDD + LEDF + LEDG;
    }
    else if(dig=='A')
    {//LEDA = 1, LEDB = 1, LEDC = 1, LEDD = 0, LEDE = 1, LEDF = 1 E LEDG = 1
     P1OUT |= LEDA + LEDB + LEDC + LEDE + LEDF + LEDG;
    }
    else if(dig=='B')
    {//LEDA = 0, LEDB = 0, LEDC = 1, LEDD = 1, LEDE = 1, LEDF = 1 E LEDG = 1
     P1OUT = LEDC + LEDD + LEDE + LEDF + LEDG;
    }
    else if(dig=='C')
    {//LEDA = 1, LEDB = 0, LEDC = 0, LEDD = 1, LEDE = 1, LEDF = 1 e LEDG = 0
     P1OUT = LEDA + LEDD + LEDE + LEDF;
    }
    else if(dig=='D')
    {//LEDA = 0, LEDB = 1, LEDC = 1, LEDD = 1, LEDE = 1, LEDF = 0 e LEDG = 1
     P1OUT = LEDB + LEDC + LEDD + LEDE + LEDG;
    }
    else if(dig=='E')
    {//LEDA = 1, LEDB = 0, LEDC = 0, LEDD = 1, LEDE = 1, LEDF = 1 e LEDG = 1
     P1OUT = LEDA + LEDD + LEDE + LEDF + LEDG;
    }
    else if(dig=='F')
    {//LEDA = 1, LEDB = 0, LEDC = 0, LEDD = 0, LEDE = 1, LEDF = 1 e LEDG = 1
     P1OUT = LEDA + LEDE + LEDF + LEDG;
    }
}
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    volatile int i;
    P1DIR |= LEDA + LEDB + LEDC + LEDD + LEDE + LEDF + LEDG + CT1;
    P2DIR |= CT2;
    P1OUT = 0;
    P2OUT = 0;
	for(;;)
	{
	    //Aqui foi utilizado a Tabela ASCII para usar os digitos
	    // 0,1,2,3,4,5,6,7,8,9 estão definidos entre 0x30 e 0x39 na tabela
	    // A,B,C,D,E,F estão definidos entre 0x41 e 0x46
	    for(i=0x30; i<=0x39; i++)
	    {
	        EscreveDigito(i);
	        P1OUT ^= CT1;
	        P1OUT ^= CT1;
	        P2OUT ^= CT2;
	        P2OUT ^= CT2;
	    }
	    for(i=0x41; i<=0x46; i++)
	    {
	        EscreveDigito(i);
	        P1OUT ^= CT1;
	        P1OUT ^= CT1;
	        P2OUT ^= CT2;
	        P2OUT ^= CT2;
	    }
	}
	return 0;
}
