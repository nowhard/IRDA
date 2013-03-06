#include "keyboard_scan.h"
#include "timer1.h"

extern unsigned char address;
extern unsigned char key_code;
unsigned char key_code_temp=0xFF;

#define KI0 0b11111101
#define KI1	0b11111110
#define KI2	0b11111011
#define KI3	0b11110111

#define KO0	0b11111011
#define KO1	0b11111101
#define KO2	0b11110111
#define KO3	0b11101111
//-------------------------------------
/*PT_THREAD(Keyboard_Scan_Process(struct pt *pt))
{
   PT_BEGIN(pt);

   while(1) 
   {
   		PT_DELAY(pt,2);
		if(key_code!=0xFF)
		{
			switch(PINC|0xF0)
			{
				case(KI0):
				{
					switch(key_code)
					{
						case(KEY_1):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_2):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_3):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_4):
						{
							PORTB&=KO3;
						}
						break;
					}
				}
				break;

				case(KI1):
				{
					switch(key_code)
					{					
						case(KEY_5):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_6):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_7):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_8):
						{
							PORTB&=KO3;
						}
						break;
					}
				}
				break;

				case(KI2):
				{
					switch(key_code)
					{
						case(KEY_9):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_0):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_CH_UP):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_CH_DOWN):
						{
							PORTB&=KO3;
						}
						break;
   					}
				}
				break;

				case(KI3):
				{
					switch(key_code)
					{
						case(KEY_V_UP):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_V_DOWN):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_MENU):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_POWER):
						{
							PORTB&=KO3;
						}
						break;
					}
				}
				break;
			}
			
			key_code=0xFF;	
			PT_DELAY(pt,2);
		}
		else
		{
			PORTB|=0x1E;
		}
		
		PORTB|=0x1E;
   }
   PT_END(pt);	
}*/
//------------------------------------
ISR(PCINT1_vect)//прерывание от портов PC0-PC3
{
	
cli();
		if(key_code!=0xFF)
		{
			switch(PINC|0xF0)
			{
				case(KI0):
				{
					switch(key_code)
					{
						case(KEY_1):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_2):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_3):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_4):
						{
							PORTB&=KO3;
						}
						break;
					}
				}
				break;

				case(KI1):
				{
					switch(key_code)
					{					
						case(KEY_5):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_6):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_7):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_8):
						{
							PORTB&=KO3;
						}
						break;
					}
				}
				break;

				case(KI2):
				{
					switch(key_code)
					{
						case(KEY_9):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_0):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_CH_UP):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_CH_DOWN):
						{
							PORTB&=KO3;
						}
						break;
   					}
				}
				break;

				case(KI3):
				{
					switch(key_code)
					{
						case(KEY_V_UP):
						{
							PORTB&=KO0;
						}
						break;

						case(KEY_V_DOWN):
						{
							PORTB&=KO1;
						}
						break;

						case(KEY_MENU):
						{
							PORTB&=KO2;
						}
						break;

						case(KEY_POWER):
						{
							PORTB&=KO3;
						}
						break;
					}
				}
				break;

				default:
				{
					PORTB|=0x1E;
				}
			}
			
			key_code=0xFF;	

		}
		else
		{
			//PORTB|=0x1E;
		}
	PCIFR&=!(1<<PCIF1);			
sei();		
}
