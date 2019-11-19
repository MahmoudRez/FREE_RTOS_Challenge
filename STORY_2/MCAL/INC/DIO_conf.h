/*
 * DIO_conf.h
 *
 *  Created on: Sep 20, 2019
 *      Author: abdelqader
 */

#ifndef DIO_CONF_H_
#define DIO_CONF_H_

#include <avr/io.h>
#define NULL (void *)0
typedef enum { NOK, OK } STD_Fun_t;

typedef enum {LCD_D4,LCD_D5,LCD_D6,LCD_D7,LCD_EN,RS,RW,PUSH_BUTTON1,PUSH_BUTTON2,LED_1,LED_2,NUM_PINS }PINS_t ;


#define PORT_A		0
#define PORT_B		1
#define PORT_C		2
#define PORT_D		3

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define OUTPUT		1
#define INPUT		0

#define HIGH		1
#define LOW			0

#define PULLUP		1
#define EXTRES		0

#define INITIALIZED			1
#define NOT_INITIALIZED		0

#define NA			0xff


typedef struct {

	uint8_t PORT;
	uint8_t PIN;
	uint8_t Dir;
	uint8_t Val;
	uint8_t Res;
	uint8_t IS_Init;

}DIO_Conf_t;


extern DIO_Conf_t DIO_Array[NUM_PINS];


#endif /* DIO_CONF_H_ */
