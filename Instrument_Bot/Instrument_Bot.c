#define  F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "UART.c" 
#include "lcd.h"
#include  "main.h"
char note1[10],note2[10],note3[10];
int timer_reset=0;
int s=0,c=0,d=0,e=0,f=0,g=0,a=0,b=0;
unsigned long cls[20];
char tim=0.0;
char x[2];
char y[2];
char z[4];
int dec=0;
int idx=0;
int len=0;
int note_number=0;
char nt[3];

////////configuration table
char sharp[1000] = {'N', 'N', 'N', 'N', 'Y', 'N', 'Y', 'N', 'N', 'N', 'Y', 'Y', 'Y', 'N', 'N', 'N', 'N', 'Y', 'N', 'Y', 'N', 'N', 'Y', 'N', 'N', 'N', 'Y', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'Y', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'Y', 'N', 'N', 'Y', 'N', 'N', 'Y', 'N', 'Y', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'Y', 'N', 'Y', 'Y', 'Y', 'Y', 'N', 'N', 'Y', 'N', 'N', 'Y', 'N', 'N', 'N', 'N', 'N', 'N'};
int octave[1000] = {4, 4, 4, 4, 3, 5, 5, 4, 4, 4, 4, 4, 4, 3, 4, 5, 6, 3, 5, 4, 5, 5, 4, 5, 5, 5, 4, 5, 5, 3, 5, 0, 5, 5, 5, 5, 3, 4, 5, 5, 5, 5, 3, 4, 4, 4, 5, 5, 2, 5, 5, 5, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 5, 5, 5, 5, 4, 4, 4, 4, 5, 4, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 0, 4, 8};

void time_calc()
{
	tim=60*(float)(((timer_reset*65536)+TCNT4)/(float)14745600);
}

ISR(TIMER4_OVF_vect)
{
	timer_reset++;
}
void data(int note_no, char str[1], char str2){
	char arr[4]={};
	note_number++;
	if(note_number>strlen(octave))
	{
		note_number=0;
	}
	itoa(octave[note_no],arr,10);
	if(str2=='P')
	{
		uart_tx_string("Piano\n");
		if(sharp[note_no]=='Y')
		strcat(arr,"#");              ///This transmits the C and when it is sharp and when it is
		uart_tx_string(strrev(strcat(arr,str)));
		uart_tx_string("\n");
		//lcd_clear();
		//lcd_string("Piano");
		//lcd_cursor(2,1);
		//lcd_string(arr);
		arr[0]='\0';
		
	}
	else
	{
		uart_tx_string("Trumpet\n");
		if(sharp[note_no]=='Y')
		strcat(arr,"#");              ///This transmits the C and when it is sharp and when it is
		uart_tx_string(strrev(strcat(arr,str)));
		uart_tx_string("\n");
		//lcd_clear();
		//lcd_string("Trumpet");
		//lcd_cursor(2,1);
		//lcd_string(arr);
		arr[0]='\0';
		
	}
}



void init_devices (void)
{
	cli(); //Clears the global interrupts
	lcd_port_config();
	S_config();
	boot_switch_pin_config();
	uart0_init();
	timer4_init();
	TIMSK4 = 0x01; //timer4 overflow interrupt enable
	sei(); //Enables the global interrupts
}

int main(void){
	init_devices();
	lcd_init();
	lcd_set_4bit();
	init_devices();
	lcd_clear();
	lcd_cursor(1,5);
/*************************************************************Boot Key*****************************************/
	while (1)
	{
		check_boot_press();
		lcd_string("Boot");
		if(switch_flag==1)						/////////Press the boot key first time to initiate data transmission
		{
			lcd_clear();
			lcd_string("Check");
			_delay_ms(200);
			break;
		}
		
	}
/****************************************************Indentification of notes************************************/
	while(1)
	{
		/*if((PINA & 0xFF) != 0xFF)
		{
			_delay_ms(3);                                 //if key is pressed wait for switch debouncing	      
		}*/
			
/*------------------------Piano-----------------------------*/		
	if((PINA & 0xFF) == 0xFE)															//   End Key
	{
		//lcd_clear();
		//lcd_cursor(1,1);
		//lcd_string("END");
		uart_tx_string("$\n");
	}
	
	/********__C__********/
	if((PINA & 0xFF) == 0xFD)															
	{
		data(note_number,"C",'P');
		//_delay_ms(10);
		while(1)
		{
			if((PINA & 0XFF) == 0xFF)break;
		}
		//_delay_ms(10);
	}
	
	/********___D__********/
	if((PINA & 0xFF) == 0xFB)															
	{
		data(note_number,"D",'P');
		while(1)
		{
			if((PINA & 0XFF) == 0xFF)break;
		}
		//_delay_ms(10);
	}
	
	/********___E__********/
	if((PINA & 0xFF) == 0xF7)															//E
	{
		data(note_number,"E",'P');
		while(1)
		{
			if((PINA & 0XFF) == 0xFF)break;
		}
		//_delay_ms(10);
	}
	
	/********___F__********/
	if((PINA & 0xFF) == 0xEF)															//F
	{
		data(note_number,"F",'P');
		while(1)
		{
			if((PINA & 0XFF) == 0xFF)break;
		}
		//_delay_ms(10);
	}
	
	/********___G__********/
	if((PINA & 0xFF) == 0xDF)/////////////////////////////////////////////////////G
	{
		data(note_number,"G",'P');
		while(1)
		{
			if((PINA & 0XFF) == 0xFF)break;
		}
		//_delay_ms(10);
	}
	
	/********___A__********/
	if((PINA & 0xFF) == 0xBF)////////////////////////////////////////////////////A
	{
		data(note_number,"A",'P');
		while(1)
		{
			if((PINA & 0XFF) == 0xFF)break;
		}
		//_delay_ms(10);
	}
	
	/********___B__********/
	if((PINA & 0xFF) == 0x7F)//////////////////////////////////////////////////B
	{
		data(note_number,"B",'P');
		while(1)
		{
			if((PINA & 0XFF) == 0xFF)break;
		}
		//_delay_ms(10);
	}
	
/*___________________________Trumpet________________________________________*/
		
		if((PINK & 0xFF) != 0xFF)
		{
			
			_delay_ms(30);                                 //if key is pressed wait for switch debouncing	      
		}
/*################******* Trumpet 1111 1110 Key***********##########################*/
            
			if(((PINK & 0xFF) == 0x06)) /////c
			{
			data(note_number,"C",'T');
			_delay_ms(10);
			}
		
/*################**********D Trumpet 1111 1101 Key********##########################*/
			if(((PINK & 0xFF) == 0x05)) /////D trumpet
			{
				data(note_number,"D",'T');
				_delay_ms(10);
			}
		
/*################**********E Trumpet 1111 1101 Key********##########################*/
	        if(((PINK & 0xFF) == 0x03)) ///// E trumpet            1111 1011
			{   
				data(note_number,"E",'T');
				_delay_ms(10);
			}
	
/*################**********F Trumpet 1111 1100 Key********##########################*/
			if(((PINK & 0xFF) == 0x04)) ////////F
			{
				data(note_number,"F",'T');
				_delay_ms(10);
			}
	
/*################**********G Trumpet 1111 1001 Key********##########################*/
			if(((PINK & 0xFF) == 0x01)) ///////G
			{
				data(note_number,"G",'T');
				_delay_ms(10);
			}

/*################**********A Trumpet 1111 1010 Key********##########################*/
	
			if(((PINK & 0xFF) == 0x02)) ///// A trumpet            
			{	
				data(note_number,"A",'T');
				_delay_ms(10);
			}
	
/*################**********B Trumpet 1111 1000 Key********##########################*/
	
			if(((PINK & 0xFF) == 0x00))
			{
				data(note_number,"B",'T');
				_delay_ms(10);
			}
	}
}
