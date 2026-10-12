#define F_CPU 16000000UL
#include <avr/io.h>

/*
* Pull-Up Circuit
	- WHEN PRESSED - LOW
	- WHEN NOT PRESSED - HIGH
*/
int main(void)
{
	//step 1: pin configuration
	DDRD &= ~(1 << DDD5);	//PORTD PIN 5 as Input.
	DDRB |= (1 << DDB5);    //PORTB PIN 5 as Output.
	while (1)
	{
		//checking PIND register for switch press.
		if(!(PIND & (1 << PIND5))) //When Pressed value in PIN becomes 0 -> !(0) -> 1
		{
			PORTB ^= (1 << PORTB5);	//LED ON when Pressed.
			
			while(!(PIND & (1 << PIND5)));
		}
	}
}


