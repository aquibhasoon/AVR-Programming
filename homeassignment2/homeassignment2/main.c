#define F_CPU 16000000UL
#include <avr/io.h>

#define LED PORTB5

void timer0_init()
{
	
	TCCR0A &= ~((1 << WGM00) | (WGM01));
	/*------------------------------------CALCULATION----------------------------------------
	Clock Frequency (F_CPU): 16 MHz (16,000,000 Hz)
	Prescaler Value: 256
	F_timer(Timer Frequency) = 16,000,000 / 256
			= 62500 Hz
	
	 Time period: 1 / frequency - 1 / Timer Frequency (F_timer)
				= 1 / (16,000,000 /256)
				= 1 / 62500
				= 0.000016
				= 16 microseconds (us)
	time taken for 1 tick is 16 us, therefore time taken for 1 overflow = time taken for 1 tick x total no of ticks
    time for 1 overflow = 16 us x 256
						= 4.96 ms (milliseconds).
	1 second = 1000 milliseconds
	there fore 1 second = 1000 / 4.96
						= 244.14 ~  244
	*/
	TCCR0B |=(1<<CS02);
	
}

void delay_1sec()
{
	for (uint8_t i=1; i<=244; ++i)
	{
		while(!(TIFR0 & (1<<TOV0)));
		
		TIFR0 |= (1<<TOV0);
	}
	
}
int main(void)
{
	timer0_init();
	DDRB |=(1<<DDB5);
	while (1)
	{
		PORTB ^=(1<<LED);
		delay_1sec();
	}
}
