
#include <msp430g2553.h>
#define ADC_CHANNELS 2
unsigned int adc[ADC_CHANNELS]=0;

void Setup(void);
void Read_ADC(void);

int main( void )
{
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer to prevent time out reset
  Setup();
  while(1)
  {
    Read_ADC();
    if(adc[0]>1000)
    {
      P1OUT |= BIT6;
      unsigned int delay = 6000;
      while(delay--);
    }
    else
    {
      P1OUT &= ~BIT6;
      unsigned int delay = 6000;
      while(delay--);
    }
  }
  return 0;
}
 
void Setup(void)
{
  BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
  DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
  P1OUT = 0;
  P1DIR |= BIT6;
  //Setup for ADC10
  
  ADC10CTL0 |=  SREF_0 +  ADC10SHT_2 + MSC + ADC10ON + ADC10IE; //Reference from Vcc and Vss,
  //sampling time of 16×ADC10CLKs, ADC10ON
  ADC10CTL1 |= INCH_1 + CONSEQ_1; //Input channel A1 and A0; repeated sequence 
  ADC10AE0 = BIT0 + BIT1; // Analog Input in P1.0 and P1.1; 
  ADC10DTC1 = ADC_CHANNELS; // 2 conversions
}

void Read_ADC(void)
{
  ADC10CTL0 &= ~ENC;
  while(ADC10CTL1 & BUSY);// Wait if ADC10 core is active
  ADC10SA = (unsigned int) adc; //Copies data in ADC10SA to unsigned int adc array
  ADC10CTL0 |= ENC + ADC10SC;
 // __bis_SR_register(CPUOFF + GIE);
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
