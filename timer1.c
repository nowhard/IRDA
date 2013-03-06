#include "timer1.h"
#define FCPU 8000000
volatile unsigned int capture, last_capture, period;
volatile unsigned char bit_counter=0;//счетчик битов
volatile unsigned char byte_counter=0;//счетчик бaйтов


volatile unsigned char address=0;
volatile unsigned char key_code=0;

/*#define START_PERIOD_MIN  3700
#define START_PERIOD_MAX  6000

#define BIT_0_MIN		  900
#define BIT_0_MAX		  1500

#define BIT_1_MIN		  1900
#define BIT_1_MAX		  2500*/
#define PRE 64UL

#define START_IMP_TH  500//(12000UL*FCPU)/PRE
#define START_IMP_MAX 700//(15000UL*FCPU)/PRE
#define BIT_IMP_MAX   350//(3000UL*FCPU)/PRE
#define BIT_IMP_TH    200//(1500UL*FCPU)/PRE

volatile unsigned char buffer[8];

//------------
unsigned int first=0, second=0,third=0;
//------------

//--------------------------------------------------
void Timer1_Init(void)//инициализация timer1
{	
	TCNT1=0x0;

	TCCR1A=(0<<COM1A1)|(0<<COM1A0)|(0<<WGM11)|(0<<WGM10);  //????? - normal, 
    TCCR1B=(0<<ICNC1)|(1<<ICES1)|(0<<WGM13)|(0<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10);
	TIMSK1|=(1<<ICIE1);
	return;
}
//----------------------------------------------------
ISR(TIMER1_CAPT_vect) //обработчик прерывания таймера0 
{
cli();	
	last_capture=capture;
	capture=ICR1;//(ICR1H<<8)|(ICR1L);
	//--------------------------
	if(capture>last_capture)
	{
		period=capture-last_capture;
	}
	else
	{
		period=(65535-last_capture)+capture;
	}
	//--------------------------
	if((period>START_IMP_TH) && (period<START_IMP_MAX))
	{
		bit_counter=0;
		byte_counter=0;
		first=period;
		buffer[0]=0;
		buffer[1]=0;
		buffer[2]=0;
		buffer[3]=0;
	}
	else
	{
		if(period<BIT_IMP_MAX)
		{	
			if(period>BIT_IMP_TH)
			{
				buffer[byte_counter]|=(1<<bit_counter);
				second=period;
			}
			bit_counter++;
			third=period;		
		}
		
		if(bit_counter==8)
		{
			byte_counter++;
			//buffer[byte_counter]=0;
			bit_counter=0;
		}

		if(byte_counter>3)
		{
			address=buffer[0];
			key_code=buffer[2];
				
			bit_counter=0;
			byte_counter=0;	
		}
	}

	TIFR1&=!(1<<ICF1);
sei();
return;
}
//---------------------------------------------------
