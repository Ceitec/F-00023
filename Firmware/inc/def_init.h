/*
 * def_init.h
 *
 * Created: 16.1.2017 17:57:17
 *  Author: atom2
 */ 


#ifndef DEF_INIT_H_
#define DEF_INIT_H_

//Velikost použitého krystalu
//#define F_CPU 16000000UL
#define F_CPU 14745600UL

//Velikost bufferu pro pøíjem dat
#define	BUFFER_CHAR_PACKET	18 // Musí být násobky 9!!!

// Adresa modulu 
#define MODULE_ADDRESS 100

// Deska Slave - Základní firmware pro Slave zaøízení
#define MODULE_TYPE	200	
// Deska Pøevodník RS485 - Pøevodník z interní na externí RS485
//#define MODULE_TYPE	201	


#define LED2_ON		sbi(PORTB, PORTB4);
#define LED2_OFF	cbi(PORTB, PORTB4);
#define LED2_TOG	nbi(PORTB, PORTB4);
#define LED1_ON		sbi(PORTB, PORTB3);
#define LED1_OFF	cbi(PORTB, PORTB3);
#define LED1_TOG	nbi(PORTB, PORTB3);
#define LED0_ON		sbi(PORTB, PORTB2);
#define LED0_OFF	cbi(PORTB, PORTB2);
#define LED0_TOG	nbi(PORTB, PORTB2);


#endif /* DEF_INIT_H_ */