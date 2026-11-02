/*
 * phase_corrected_PWM.c
 *
 * Created: 23-10-2026 22:12:28
 * Author : aquib
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



void  timer0_fast_pwm_init()
{
	//step 1: configuring PD6 as Output (OCR0A)
	DDRD |= (1 << DDD6);
	//step 2: configuring timer0 in fast pwm mode
	TCCR0A |= (1 << WGM00);
	
	/*----------------------calculation----------------------------
	
	F_pwm = F_CPU / (2 * N * 256), where N = Prescaler value
	F_CPU = 16,000,000 Hz
	N = 64
	
	F_pwm = 16,000,000 / (2 x 64 x 256)
		  = 488.28 Hz ~ 0.5 KHz		  

	*/
	//step 4: configuring prescaler value as 64
	TCCR0B |= ((1 << CS01) | (1 << CS00));
	TCCR0B &= ~(1 << CS02);
	//step 5: configuring in non-inverting mode
	TCCR0A |= (1 << COM0A1);
	
}


int main(void)
{
    timer0_fast_pwm_init();
    while (1) 
    {
		for (uint8_t i=0;i<255;++i)
		{
			OCR0A = i;
			_delay_ms(100);
			
		}
		for (uint8_t i=255;i>0;--i)
		{
			OCR0A = i;
			_delay_ms(50);
			
		}
	
    }
}

