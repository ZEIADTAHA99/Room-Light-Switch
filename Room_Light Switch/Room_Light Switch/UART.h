/*
 * UART.h
 *
 * Created: 28/09/2023 02:18:20 PM
 *  Author: ziad
 */ 


#ifndef UART_H_
#define UART_H_


// UART headers
void UART_INIT(unsigned int baud);
void UART_sendchar(unsigned char data);
unsigned char UART_receivechar();
void UART_sendString(char *str);

void UART_send_byte( char byte);
char  UART_recieve_byte(void);
void  UART_recieve_string(char * ptr);


#endif /* UART_H_ */