/**
 * Seven Segment Display Counter
 * 
 * 4 Digit 7 Segment Display Counter for the ATMega32
 * 
 * Author       : Julian Labuschagne
 * Date         : 2014/12/09
 * Last Updated : 2014/11/09
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME 3

#define DIG_1  ~(1 << 0)
#define DIG_2  ~(1 << 1)
#define DIG_3  ~(1 << 2)
#define DIG_4  ~(1 << 3)

#define SEG_A  (1 << 0)
#define SEG_B  (1 << 1)
#define SEG_C  (1 << 2)
#define SEG_D  (1 << 3)
#define SEG_E  (1 << 4)
#define SEG_F  (1 << 5)
#define SEG_G  (1 << 6)
#define SEG_DP (1 << 7)

int digits[] = {DIG_1, DIG_2, DIG_3, DIG_4}; 

uint8_t numbers[] = {
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E| SEG_F, 		// Digit 0
	SEG_B | SEG_C, 						// Digit 1
	SEG_A | SEG_B | SEG_D | SEG_E | SEG_G, 			// Digit 2
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,			// Digit 3
	SEG_B | SEG_C | SEG_F | SEG_G,				// Digit 4
	SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,			// Digit 5
	SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,		// Digit 6
	SEG_A | SEG_B | SEG_C,					// Digit 7
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,	// Digit 8
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,		// Digit 9
	SEG_DP, 						// Decimal Point
};

void display_number(int number) {
	for(int i = 0; i < 4; i++) {
		PORTA = digits[i];
		PORTB = numbers[number % 10];
		_delay_ms(DELAY_TIME);
		PORTB = 0;
		number = number / 10;
		PORTA = 0;
	}
}

int main(void) {
	
	// -------- Inits -------- //
	DDRB = 0xff;
	PORTB = (1 << 0);

	DDRA = 0xff;
	PORTA = 0xff;

	TCCR1B |= 1 << CS12; // Enable the clock with a prescaler CLK IO / 256
	
	// ------ Event loop ----- //

	int count = 0; 
	while (1) {
		if(TCNT1 > 62500) {
			TCNT1 = 0;
			if (count < 10000) {
				count++;
			}
			else {
				count = 0;
			}
		}
		display_number(count);
	}
	
	return 0;
}

