


#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>


volatile uint16_t overflow_count =0;

ISR (TIMER0_COMPA_vect)
{
	PORTB ^=(1<<PORTB5);
	
}

void GPIO_innit()
{
	DDRB |=(1<<DDB5);
	PORTB &= ~(1<<PORTB5);
	
}


void interrupt_timer0_ctc_innit()
{
	TCNT0 =0;
	TCCR0A |= (1<<WGM01);
	/*  
	Calculation
	
	F_cpu=16MHz
	Prescalar =256
	F_timer=16MHz/256
		  =62500Hz
	T_tick=1/F_timer=0.000016
					=16us
	Req delay=2ms
	req ticks= (req delay/t_tick)-1
			 =(2000/16)-1
			 =125-1
			 =124
	*/
	TCCR0B |= (1<<CS02);
	TIMSK0 |= (1<<OCIE0A);
	OCR0A=124;
	
}

int main(void)
{
	GPIO_innit();
    interrupt_timer0_ctc_innit();
	sei();-
	-
	
	 
    while (1) 
    {
    }
}

