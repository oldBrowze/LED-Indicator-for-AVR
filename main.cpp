#define F_CPU 160000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LED_core.hpp"


int main()
{

	LED_I::port_init();
    while(true)
	{
		for(uint16_t i = 0; i < 9999; ++i)
		{
			LED_I::print_value(i);
			_delay_ms(25);
		}
		
	}
}

