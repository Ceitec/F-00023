/*
 * Firmware.c
 *
 * Created: 8.2.2017 17:30:24
 * Author : atom2
 */ 
// Z�kladn� Firmware pro jak�koliv Slave za��zen�
/*
Nastaven� fuse bits
	High		0x91
	Low			0xD7
	Extended	0xFC
	Bez Bootloader re�imu
*/



#include <avr/io.h>

#include "inc/def_init.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <string.h>
#include <avr/eeprom.h>
#include "inc/common_defs.h"
#include "inc/def_init.h"
#include "inc/uart0.h"
#include "inc/trinamic.h"
#include "inc/timer.h"
#include "inc/board.h"


uint8_t uart0_error=0,uart1_error=0;

// Deklarov�n� prom�nn�ch z uart0.c
uint8_t uart0_rx_ptr;
uint8_t uart0_buf_rx[BUFFER_CHAR_PACKET];

uint8_t uart0_tx_flag;
uint8_t uart0_tx_ptr;
uint8_t uart0_tx_iptr;

uint8_t uart0_rx_flag;
uint8_t uart0_rx_ptr;
uint8_t uart0_rx_iptr;

Trinamicpac TB_Buf_In;
Trinamicpac TB_Buf_Out;



uint32_t UB = 0;

uint16_t citacka0, citacka1;

void try_receive_data(void)
{
	uint8_t j=0;
 	j = check_uart0();
	// Data byla p�ijata
 	if (j == 1)
	{
		// Napln� Buffer trinamic
		TB_buf_fill_In();
		// Kontrola adresy, jestli je adresa schodn� s adresou modulu
		if (TB_Buf_In.n.addr == TB_gbparam.address)
		{
			// Rozebr�n� p��kazu
			switch (TB_Process())
			{
				// Zde se vypisuj� p��kazy u�ivatelsk�, kter� chceme implementovat
				case TB_CMD_SIO:
					switch(TB_Buf_In.b[TB_BUF_TYPE])
					{
						case 0:
							switch(TB_Buf_In.b[TB_BUF_MOTOR])
							{
								case 0:
									TB_SendAck(TB_ERR_OK, 0);
									break;
								default:
									TB_SendAck(TB_ERR_MOTOR, TB_Buf_In.b[TB_BUF_MOTOR]);
									break;
							}
							break;
						default:
							TB_SendAck(TB_ERR_TYPE, TB_Buf_In.b[TB_BUF_TYPE]);
							break;
					}
				case TB_CMD_GIO:
					switch(TB_Buf_In.b[TB_BUF_TYPE])
					{
						case 0:
							switch(TB_Buf_In.b[TB_BUF_MOTOR])
							{
								case 0:
									TB_SendAck(TB_ERR_OK, 0);
									break;
								default:
									TB_SendAck(TB_ERR_MOTOR, TB_Buf_In.b[TB_BUF_MOTOR]);
									break;
							}
							break;
						default:
							TB_SendAck(TB_ERR_TYPE, TB_Buf_In.b[TB_BUF_TYPE]);
							break;
					}
			}
		}		
	}
}


int main(void)
{
	// Mus� b�t ulo�en� do prom�nn� nejprve!! Jinak doch�z� k probl�mu s nastaven�m UBRRL
	UB = UART0_DEFAULT_BAUD;
	uart0_error = uart0_init(UB);
	uart0_interrupt_rx(TRUE);
	uart0_interrupt_tx(TRUE);
	
	TB_Init();
	
	Init_Board();
	
	// Povolen� glob�ln�ho p�eru�en�
	sei();

	// Hlavn� smy�ka programu
	while (1) 
    {
		// Kontroluje p��jem dat a rozhodovac� logika pro odpov��
		try_receive_data();
		// Jednoduch� nulov�n� flagu pro p��jem
		simple_flag_null();
		
    }
}


