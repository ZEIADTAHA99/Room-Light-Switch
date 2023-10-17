/*
 * Room_light_Switch_Receive.c
 *
 * Created: 28/09/2023 05:51:12 PM
 * Author : ziad
 */ 

#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // header interrupt



void motor(unsigned char d,unsigned char r);
void motor_Servo(unsigned char d);

// macros
#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)

#include "UART.h"
#include "interrupt.h"

int main(void)
{
	UART_INIT(103);
	int1_init();
	int0_init();
	unsigned char x;
	
	setbit(DDRC,6); // Open RED LED
	setbit(DDRC,5); // Close LED
	setbit(DDRA,6); // Testing LEDs
	setbit(DDRA,7);// Testing LEDs
	
    setbit(DDRB,1);
	
	setbit(DDRD,5); // OUTPUT for Servo Motor
	


	while (1)
	{
	    x = UART_receivechar();
		//UART_sendchar(x);
		//Controlling From Mobile Pone (Bluetooth Application) :
		
		if (x == 'o') // Open Switch INT1 111 ASCI
		{
			setbit(PORTC,6);  // Alarm RED LED (On)
			clearbit(PORTC,5);  // Green LED   (off)
		
			TCCR1A = (1<<WGM11)|(1<<COM1A1);
			TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
			ICR1=39999;  //fPWM=50Hz (Period = 20ms Standard).
			TCNT1=0;
			//DDRB|=(1<<PORTB4)|(1<<PORTB5); //PWM Pins as Out
			setbit(DDRB,1); 
			setbit(DDRB,5); 
			OCR1A=(1200);//5250 //2100 //1900
				
		}
		
		
		else if (x == 'c') // Close Switch INT0 //99 ASCI
		{
			setbit(PORTC,5);  // Green LED
			clearbit(PORTC,6);  // Alarm RED LED
			
			setbit(PORTA,6);
			_delay_ms(100);
			clearbit(PORTA,6);
			_delay_ms(100);
			
			TCCR1A = (1<<WGM11)|(1<<COM1A1);
			TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
			ICR1=39999; //fPWM=50Hz (Period = 20ms Standard).
			TCNT1=0;
			//DDRB|=(1<<PORTB4)|(1<<PORTB5); //PWM Pins as Out
			setbit(DDRB,1);
			setbit(DDRB,5);
			OCR1A=(840);//1600	//1500 //1800  // so far ok
		}
		
		
	}
}


// Controlling By Interrupts Push Buttons:

ISR(INT1_vect)
{
	
	UART_sendchar('o');// Open Switch
	
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR1=39999;  //fPWM=50Hz (Period = 20ms Standard).
	TCNT1=0;
	//DDRB|=(1<<PORTB4)|(1<<PORTB5); //PWM Pins as Out
	setbit(DDRB,1);
	setbit(DDRB,5);
	OCR1A=(1200);//5250 //2100 //1900
	
}

ISR(INT0_vect)
{
	
	UART_sendchar('c'); // Close Switch
	
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR1=39999; //fPWM=50Hz (Period = 20ms Standard).
	TCNT1=0;
	//DDRB|=(1<<PORTB4)|(1<<PORTB5); //PWM Pins as Out
	setbit(DDRB,1);
	setbit(DDRB,5);
	OCR1A=(840);//1600	//1500 //1800  // so far ok
	
}


