#ifndef _LED_CORE_HPP
#define _LED_CORE_HPP

#include <avr/interrupt.h>
#include <avr/pgmspace.h>

namespace LED_I
{
	uint8_t _digit;
	uint16_t _number;
	const uint8_t _numbers[10] PROGMEM =
	{
		0b00111111,//0
		0b00000110,//1
		0b01011011,//2
		0b01001111,//3
		0b01100110,//4
		0b01101101,//5
		0b01111101,//6
		0b00000111,//7
		0b01111111,//8
		0b01101111//9
	};
	
	inline const uint8_t get_value(const uint16_t &number, const uint8_t &_digit)
	{
		switch(_digit)
		{
			case 0: return number % 10;
			case 1: return (number < 10) ? 0 : number % 100 / 10;
			case 2: return (number < 100) ? 0 : number % 1000 / 100;
			case 3: return (number < 1000) ? 0 : number / 1000;
			default: return 0;
		}
	}
	inline void print_value(const uint16_t &number)
	{
		_number = number;
	}
	inline void port_init()
	{
		#ifndef LED_UPDATE
			#define LED_UPDATE 3
		#endif
		#if LED_UPDATE == 4
			TCCR0B = 0b00000101;//1024
		#elif LED_UPDATE == 3
			TCCR0B = 0b00000100;//256
		#elif LED_UPDATE == 2
			TCCR0B = 0b00000011;//64
		#elif LED_UPDATE == 3
			TCCR0B = 0b00000010;//8
		#elif LED_UPDATE == 2
			TCCR0B = 0b00000100;//1
		#else
			TCCR0B = 0b00000100;//256
		#endif
		
		//TCCR0B = 0b00000100;
		TIMSK0 = 0x1;
		sei();
		
		DDRD = 0xFF;
		DDRB = 0xFF;
	}
	SIGNAL(TIMER0_OVF_vect)
	{
		PORTB = (1 << _digit);
		PORTD = pgm_read_byte(&_numbers[get_value(_number, _digit)]);
		if(++_digit > 3)
		_digit = 0;
	}
};


#endif