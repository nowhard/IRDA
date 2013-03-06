
#include<avr/interrupt.h>
#include "timer1.h"
#include "timer0.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include <string.h>

 #include <avr/wdt.h> 
#include "pt/pt.h"
#include "uart.h"



volatile struct pt pt1, pt2,pt_key,pt_blink;
//extern unsigned char display_mask;
extern unsigned int period;
extern unsigned char address;
extern unsigned char key_code;

void Port_Init(void);


FILE uart_str = FDEV_SETUP_STREAM(&uart_putchar, &uart_getchar, _FDEV_SETUP_RW);
PT_THREAD(Display_Out_Process(struct pt *pt));
extern unsigned int capture;
extern unsigned int first,second,third;
//-----------------------------------------------
int main(void)
{
stdin = &uart_str;
stdout = &uart_str;

//poutoutput = USART0; 

Timer0_Init();
Port_Init();

Timer1_Init();
UART_Init();
//wdt_enable(WDTO_1S);
	//PT_INIT(&pt1);

sei();

/*	while(1)//init loop
	{
		unsigned char state=0;
		state=ClockInit(&pt1);
		if(state==PT_ENDED)
		{
			break;
		}
	}*/
	PT_INIT(&pt1);
   // PT_INIT(&pt2);
//	PT_INIT(&pt_key);
//	PT_INIT(&pt_blink);
	while(1)
	{
		Display_Out_Process(&pt1);
	//	wdt_reset();
	}
}
//-----------------------------------------------
void Port_Init(void)
{
	//DDRB=0xFF;
	DDRD=0x2;//RX-in TX-out
	DDRD|=0x10;
	PORTD|=0x14;

	DDRC=0xF;
	PORTC=0x0;

	PORTB=0x0;
	PORTB |= _BV(PB0);
}
//-----------------------------------------------
ISR(TIMER0_OVF_vect) //���������� ���������� �������0 
{
//cli();
	pt1.pt_time++;
	pt2.pt_time++;
	//pt_key.pt_time++;
	//pt_blink.pt_time++;

//	PORTB^=0x40;

	TCNT0=130;
	TIFR0&=0b11111110;//TIFR0&=!(1<<TOV0);
	
//sei();
}
//-----------------------------------------------------------------------------
PT_THREAD(Display_Out_Process(struct pt *pt))
 {

   PT_BEGIN(pt);

   while(1) 
   {
	 PT_DELAY(pt,1000);
	 printf("address= %u, key code= %u",address,key_code);
	 //printf("first=%u,second=%u,third=%u",first,second,third);	
   }
   PT_END(pt);
 }
//-----------------------------------------------------------------------------
