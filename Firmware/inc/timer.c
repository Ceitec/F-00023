/*
 * timer.c
 *
 * Created: 1.2.2017 11:01:37
 *  Author: atom2
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>


volatile uint16_t citacka0=0;
volatile uint16_t citacka1=0;

uint8_t uart0_rx_ptr;
uint8_t uart0_rx_iptr;


void simple_flag_null( void )
{
	if (citacka0 > 10000)
	{
		// Vyma�e ka�d�ch 50ms flag intern� ��ta�
		uart0_rx_iptr=0;
		uart0_rx_ptr=0;
		citacka0=0;
	}
	citacka0++;
}