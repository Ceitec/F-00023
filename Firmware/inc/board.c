/*
 * board.c
 *
 * Created: 10.2.2017 14:31:02
 *  Author: atom2
 */ 


#include <avr/io.h>
#include "def_init.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "common_defs.h"
#include "trinamic.h"

void Init_Board( void )
{
	// Nastaven� RS485 Enable Intern�
	sbi(DDRD, DDD2);
	// UART0 RX
	cbi(DDRD, DDD0);
	// UART0 TX
	sbi(DDRD, DDD1);
	
	// LED0 V�stupn� pin PB2
	sbi(DDRB, DDB2);
	// LED1 V�stupn� pin PB3
	sbi(DDRB, DDB3);
	// LED2 V�stupn� pin PB4
	sbi(DDRB, DDB4);
	
	LED0_OFF;
	LED1_OFF;
	LED2_OFF;
	
	// Povolen� p�ijmu dat
	RS485_EN_INT_receive;
}