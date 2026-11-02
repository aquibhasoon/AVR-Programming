/*
 * interrupt_normal_mode.c
 *
 * Created: 29-10-2026 10:15:20
 * Author : aquib
 */ 


#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>


volatile uint16_t overflow_count =0;

ISR (TIMER0_OVF_vect)
{
	overflow_count++;
	if (overflow_count>=977)
	{
		PORTB ^=(1<<PORTB5);
		overflow_count=0;
	}
}

void GPIO_innit()
{
	DDRB |=(1<<DDB5);
	PORTB &= ~(1<<PORTB5);
	
}


void interrupt_timer0_normal_innit()
{
	TCNT0 =0;
	TCCR0A &= ~((1<<WGM00)| (1<<WGM01));
	/* 
	Calculation
	
	F_cpu=16MHz
	Prescalar =64
	F_timer=16MHz/64
		  =250KHz
	T_tick=1/F_timer=0.000004
					=4us
	Overflow time =total overflow count *t_tick
				  =256*4
				  =1.024
	So, Overflow for 1 sec=1000ms
				for 1.024=1000/1.024=976.56~ 977
	*/
	TCCR0B |= ((1<<CS01)|(1<<CS00));
	TIMSK0 |= (1<<TOIE0);
	
}

int main(void)
{
	GPIO_innit();
    interrupt_timer0_normal_innit();
	sei();
    while (1) 
    {
    }
}

