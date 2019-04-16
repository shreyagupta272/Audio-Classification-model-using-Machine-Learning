/*
* Team Id: MB#532
* Author List: Shreya Gupta, Ram Mahesh,Pragya Vyas,Abhishek Kumar
* Filename: main.h
* Theme: Mocking Bot
* Functions:
* Global Variables: 
*/
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define BAUD 9600                                  // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)
void timer5_init();
void lcd_string(char*);	
int switch_flag = 0;
void boot_switch_pin_config()
{
	DDRD  = DDRD & 0xBF;		// set PD.6 as input
	PORTD = PORTD | 0x40;		// set PD.6 HIGH to enable the internal pull-up
}
void timer4_init(void)
{
	TCCR4B = 0x00; //stop
	TCNT4H = 0xF9; //Counter higher 8 bit value
	TCNT4L = 0xB3; //Counter lower 8 bit value
	OCR4AH = 0x00; //Output Compare Register (OCR)- Not used
	OCR4AL = 0x00; //Output Compare Register (OCR)- Not used
	OCR4BH = 0x00; //Output Compare Register (OCR)- Not used
	OCR4BL = 0x00; //Output Compare Register (OCR)- Not used
	OCR4CH = 0x00; //Output Compare Register (OCR)- Not used
	OCR4CL = 0x00; //Output Compare Register (OCR)- Not used
	ICR4H  = 0x00; //Input Capture Register (ICR)- Not used
	ICR4L  = 0x00; //Input Capture Register (ICR)- Not used
	TCCR4A = 0x00;
	TCCR4C = 0x00;
	TCCR4B = 0x03; //start Timer
}
void check_boot_press()
{
	if ((PIND & 0x40) == 0x40)
	{
		switch_flag = 0;
	}
	else
	{
		switch_flag = 1;
		uart_tx_string("#");
		uart_tx_string("\n");
	}
}

void S_config()
{
	DDRA  = DDRA & 0x00;		// set ALL_HIGH
	PORTA = PORTA | 0xFF;		// set All HIGH to enable the internal pull-up
}

void St_config()
{
	DDRK  = DDRK & 0xF8;		// set 3 PINS INPUT
	PORTK = PORTK | 0x07;		// set All HIGH to enable the internal pull-up
}


