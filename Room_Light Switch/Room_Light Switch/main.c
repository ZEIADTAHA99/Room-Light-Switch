/*
 * Room_Light Switch.c
 *
 * Created: 28/09/2023 02:14:55 PM
 * Author : ziad
 */ 

// Master Micro-Controller (Sending) :

#define F_CPU 16000000ul
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h> // header interrupt

// macros
#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit) ((reg>>bit)&1)		// input read

#include "LCD.h"
#include "UART.h"
#include "interrupt.h"


int main(void)
{
	UART_INIT(103);      // init baud = 9600
	int1_init();        
	int0_init();
	
	setbit(DDRA,6);
	setbit(DDRA,7);
	
	setbit(DDRD,5);  
	
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
	
}

ISR(INT1_vect)
{
	//DDRC=0XFF;
	UART_sendchar('o');// Open Switch
	
	setbit(PORTA,7);
	_delay_ms(100);
	clearbit(PORTA,7);
	_delay_ms(100);
	
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR1=39999;  //fPWM=50Hz (Period = 20ms Standard).
	TCNT1=0;
	//DDRB|=(1<<PORTB4)|(1<<PORTB5); //PWM Pins as Out
	setbit(DDRB,1);
	setbit(DDRB,5);
	OCR1A=(5250);
	
	
}

ISR(INT0_vect)
{
	//DDRC=0XFF;
	//int x;
	UART_sendchar('c'); // Close Switch
	
	
	setbit(PORTA,6);
	_delay_ms(100);
	clearbit(PORTA,6);
	_delay_ms(100);
	
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR1=39999;  //fPWM=50Hz (Period = 20ms Standard).
	TCNT1=0;
	//DDRB|=(1<<PORTB4)|(1<<PORTB5); //PWM Pins as Out
	setbit(DDRB,1);
	setbit(DDRB,5);
	OCR1A=(1600);
	
	
}



/*
//LCD_send_string ("RelativeMeaning:");// displaying name
LCD_send_command(0x80 + 0x40 + 0);// shifting cursor  to 1st  shell  of second line
//_delay_ms(10);
LCD_send_string(" CLOSE ");
//LCD_send_string(" ");
_delay_ms(60);
//LCD_send_command(0x01);
*/