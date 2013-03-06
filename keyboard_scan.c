#include "keyboard_scan.h"
#include "timer1.h"

extern unsigned char address;
#define DEV_ADDR 32
extern unsigned char key_code;
unsigned char key_code_temp=0xFF;

volatile unsigned char port_temp=0xFF, interrupt_temp=0x0;

#define KI0 0b00000010//0b11111101
#define KI1	0b00000001//0b11111110
#define KI2	0b00000100//0b11111011
#define KI3	0b00001000//0b11110111

/*#define KO0	0b11111011
#define KO1	0b11111101
#define KO2	0b11110111
#define KO3	0b11101111*/

#define KO0	0b00000100
#define KO1	0b00000010
#define KO2	0b00001000
#define KO3	0b00010000

volatile unsigned char flag_key_delay=0;
//------------------------------------
ISR(PCINT1_vect)//прерывание от портов PC0-PC3
{	
//cli();
	/*if((PORTB|0xE1)==0xFF)
	{
    	PORTB=port_temp;
	}
	else
	{
		PORTB|=0x1E;
	}*/
	PORTB^=port_temp;
	PCIFR&=!(1<<PCIF1);			
//sei();		
}
//--------------------------------------
PT_THREAD(Delay_Key_Process(struct pt *pt))
{	
   PT_BEGIN(pt);

   while(1) 
   {
		PT_WAIT_UNTIL(pt,(key_code!=0xFF && address==DEV_ADDR));
		printf("address= %u, key code= %u  ",address,key_code);
		//-----------------------------------
				port_temp=0xFF;
				interrupt_temp=0x0;
				switch(key_code)
				{
					case(KEY_1):
					{
						port_temp=KO0;
						interrupt_temp=(KI0);
					}
					break;

					case(KEY_2):
					{
						port_temp=KO1;
						interrupt_temp=(KI0);
					}
					break;

					case(KEY_3):
					{
						port_temp=KO2;
						interrupt_temp=(KI0);
					}
					break;

					case(KEY_4):
					{
						port_temp=KO3;
						interrupt_temp=(KI0);
					}
					break;
					//---------------------------------					
					case(KEY_5):
					{
						port_temp=KO0;
						interrupt_temp=(KI1);
					}
					break;

					case(KEY_6):
					{
						port_temp=KO1;
						interrupt_temp=(KI1);
					}
					break;

					case(KEY_7):
					{
						port_temp=KO2;
						interrupt_temp=(KI1);
					}
					break;

					case(KEY_8):
					{
						port_temp=KO3;
						interrupt_temp=(KI1);
					}
					break;
					//---------------------------------
					case(KEY_9):
					{
						port_temp=KO0;
						interrupt_temp=(KI2);
					}
					break;

					case(KEY_0):
					{
						port_temp=KO1;
						interrupt_temp=(KI2);
					}
					break;

					case(KEY_CH_UP):
					{
						port_temp=KO2;
						interrupt_temp=(KI2);
					}
					break;

					case(KEY_CH_DOWN):
					{
						port_temp=KO3;
						interrupt_temp=(KI2);
					}
					break;
					//------------------------------------
					case(KEY_V_UP):
					{
						port_temp=KO0;
						interrupt_temp=(KI3);
					}
					break;

					case(KEY_V_DOWN):
					{
						port_temp=KO1;
						interrupt_temp=(KI3);
					}
					break;

					case(KEY_MENU):
					{
						port_temp=KO2;
						interrupt_temp=(KI3);
					}
					break;

					case(KEY_POWER):
					{
						port_temp=KO3;
						interrupt_temp=(KI3);
					}
					break;
				}
				

			printf("INT MASK= %u, port= %u",interrupt_temp,port_temp);

				PCMSK1|=interrupt_temp;
				PCICR|=(1<<PCIE1);

			
		//-----------------------------------
	 	PT_DELAY(pt,150);
		PORTB|=0x1E;
		key_code=0xFF;
		PCICR&=!(1<<PCIE1);
		PCMSK1=0x0;
   }
   PT_END(pt);
}
