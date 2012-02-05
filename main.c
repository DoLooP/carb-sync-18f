#include <p18f2550.h>
#include <delays.h>
#include <usart.h>
#include <adc.h>
#include <stdio.h>

#pragma config FOSC = HSPLL_HS
#pragma config PLLDIV = 5
#pragma config CPUDIV = OSC1_PLL2
//#pragma config USBDIV = 2

#pragma config WDT = OFF //Disable watchdog timer

#define LEDPin LATAbits.LATA0 //Define LEDPin as PORT A Pin 0
#define LEDTris TRISAbits.RA0 //Define LEDTris as TRISA Pin 0

const char* CSI = "\x1b[";

int ADC_call(char );
void cls();
void goto00();

void goto00()
{
	printf(CSI);
	printf(";H");
}

void cls()
{
	printf(CSI);
	printf("2J");	
}

int ADC_call(char c)
{
	int adc;
	char ADC_CHAN;
	if (c == 0)
		ADC_CHAN = ADC_CH9;
	else if (c == 1)
		ADC_CHAN = ADC_CH8;
	else if (c == 2)
		ADC_CHAN = ADC_CH10;
	else
		ADC_CHAN = ADC_CH12;

	OpenADC(ADC_FOSC_2 & ADC_LEFT_JUST & ADC_20_TAD
	, ADC_CHAN & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS
	, 0);	
	Delay10TCYx(5);  // Delay for 5us
	ConvertADC();  // Start conversion
	while(BusyADC()); // wait for completion
	adc = ReadADC();  // Read result
	CloseADC();  // Disable A/D converter
	return adc;	
}

void main()
{
	LEDTris = 0;//Set LED Pin data direction to OUTPUT
	LEDPin = 1;//Set LED Pin

	OpenUSART( USART_TX_INT_OFF  &
           USART_RX_INT_OFF  &
           USART_ASYNCH_MODE &
           USART_EIGHT_BIT   &
           USART_CONT_RX     &
           USART_BRGH_HIGH,
           77); // 38400 bps, set your virtual com port to that speed!


	cls();
	while(1)
	{
		int i;
	    LEDPin = ~LEDPin;//Toggle LED Pin
		printf("%i\r\n", ADC_call(0));
		printf("%i\r\n", ADC_call(1));
		printf("%i\r\n", ADC_call(2));
		printf("%i\r\n", ADC_call(3));
		goto00();		

		i = 1;
		while(i--)
			Delay10KTCYx(0);
	}

}