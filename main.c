#include <p18f2550.h>
#include <delays.h>
#include <usart.h>
#include <stdio.h>

#pragma config FOSC = HSPLL_HS
#pragma config PLLDIV = 5
#pragma config CPUDIV = OSC1_PLL2
//#pragma config USBDIV = 2

#pragma config WDT = OFF //Disable watchdog timer

#define LEDPin LATAbits.LATA0 //Define LEDPin as PORT A Pin 0
#define LEDTris TRISAbits.RA0 //Define LEDTris as TRISA Pin 0

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


	while(1)
	{
		int i;
		//char is[16];
	    LEDPin = ~LEDPin;//Toggle LED Pin
		//putsUSART( "Hello world !\r\n" );
		printf("    ~~~~"); //,i,1000000/ (16 * (i+1)));
		//putsUSART( is );

		i = 5;
		while(i--)
			Delay10KTCYx(0);
	}
	
}