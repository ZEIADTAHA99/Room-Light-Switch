/*
 * interrupt.c
 *
 * Created: 17/10/2023 06:49:52 PM
 *  Author: ziad
 */ 



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // header interrupt


// macros
#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit) ((reg>>bit)&1)		// input read

#include "interrupt.h"

void int1_init()
{
	clearbit(DDRD,3);    // set pin as INPUT //3
	setbit(MCUCR,ISC11); // The rising edge of INT1 generates an interrupt request.
	setbit(MCUCR,ISC10); // The rising edge of INT1 generates an interrupt request.
	setbit(GICR,INT1);   // external interrupt  EN  INT1
	sei();               // global interrupt EN
}


void int0_init()
{
	clearbit(DDRD,2);    // set pin as INPUT
	setbit(MCUCR,ISC01); // The rising edge of INT1 generates an interrupt request.
	setbit(MCUCR,ISC00); //The rising edge of INT1 generates an interrupt request.
	setbit(GICR,INT0);   // external interrupt  EN INT0
	sei();               // global interrupt EN
}
