#include "uart.h" 

void UART_Init(void)//������������� uart
{	
	UBRR0H=0;
	UBRR0L=0x8;

	UCSR0B|=(/*(0<<RXCIE0)|(1<<TXCIE0)|*/(1<<RXEN0)|(1<<TXEN0));	
	UCSR0C|=((0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00));
	//UBRRH=0x; //9600bit/s FCLK=8000000
}
//-----------------------------------
int
uart_putchar(char c, FILE *stream)
{

  if (c == '\a')
    {
      fputs("*ring*\n", stderr);
      return 0;
    }

  if (c == '\n')
    uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;

  return 0;
}
//-------------------------------------------------------------
int
uart_getchar(FILE *stream)
{
  uint8_t c;
  char *cp, *cp2;
  static char b[RX_BUFSIZE];
  static char *rxp;

  if (rxp == 0)
    for (cp = b;;)
      {
	loop_until_bit_is_set(UCSR0A, RXC0);
	if (UCSR0A & _BV(FE0))
	  return _FDEV_EOF;
	if (UCSR0A & _BV(DOR0))
	  return _FDEV_ERR;
	c = UDR0;
	
	if (c == '\r')
	  c = '\n';
	if (c == '\n')
	  {
	    *cp = c;
	    uart_putchar(c, stream);
	    rxp = b;
	    break;
	  }
	else if (c == '\t')
	  c = ' ';

	if ((c >= (uint8_t)' ' && c <= (uint8_t)'\x7e') ||
	    c >= (uint8_t)'\xa0')
	  {
	    if (cp == b + RX_BUFSIZE - 1)
	      uart_putchar('\a', stream);
	    else
	      {
		*cp++ = c;
		uart_putchar(c, stream);
	      }
	    continue;
	  }

	switch (c)
	  {
	  case 'c' & 0x1f:
	    return -1;

	  case '\b':
	  case '\x7f':
	    if (cp > b)
	      {
		uart_putchar('\b', stream);
		uart_putchar(' ', stream);
		uart_putchar('\b', stream);
		cp--;
	      }
	    break;

	  case 'r' & 0x1f:
	    uart_putchar('\r', stream);
	    for (cp2 = b; cp2 < cp; cp2++)
	      uart_putchar(*cp2, stream);
	    break;

	  case 'u' & 0x1f:
	    while (cp > b)
	      {
		uart_putchar('\b', stream);
		uart_putchar(' ', stream);
		uart_putchar('\b', stream);
		cp--;
	      }
	    break;

	  case 'w' & 0x1f:
	    while (cp > b && cp[-1] != ' ')
	      {
		uart_putchar('\b', stream);
		uart_putchar(' ', stream);
		uart_putchar('\b', stream);
		cp--;
	      }
	    break;
	  }
      }

  c = *rxp++;
  if (c == '\n')
    rxp = 0;

  return c;
}
