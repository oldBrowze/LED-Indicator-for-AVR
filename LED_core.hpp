#ifndef _LED_CORE_HPP
#define _LED_CORE_HPP


#define ANODE	1
#define CATHODE 2
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#if (!defined(LED_COMMON) || (LED_COMMON != ANODE && LED_COMMON != CATHODE))
	#error Declare the "LED_COMMON" macro with the value ANODE or CATHODE
#endif
#if (!defined(LED_UPDATE) || (LED_UPDATE > 5 || LED_UPDATE < 1))
	#error Declare the "LED_UPDATE" macro with a value from 1 to 5
#endif
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
		#if LED_UPDATE == 5
			TCCR0B = 0b00000101;//1024
		#elif LED_UPDATE == 4
			TCCR0B = 0b00000100;//256
		#elif LED_UPDATE == 3
			TCCR0B = 0b00000011;//64
		#elif LED_UPDATE == 2
			TCCR0B = 0b00000010;//8
		#elif LED_UPDATE == 1
			TCCR0B = 0b00000100;//1
		#endif
		//TCCR0B = 0b00000100;
		TIMSK0 = 0x1;
		sei();
		DDRD = 0xFF;
		DDRB = 0xFF;
		#if LED_COMMON == ANODE
			PORTB = 0xFF;
		#endif
	}
	SIGNAL(TIMER0_OVF_vect)
	{
		#if LED_COMMON == CATHODE
			PORTB = (1 << _digit);//катод
		#elif LED_COMMON == ANODE
			PORTB &= ~(1 << _digit);//анод
		#endif
		PORTD = pgm_read_byte(&_numbers[get_value(_number, _digit)]);
		if(++_digit > 3)
		_digit = 0;
	}
};


#endif