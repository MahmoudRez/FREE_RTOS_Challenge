/*
 * LED.c
 *
 *  Created on: Nov 15, 2019
 *      Author: alx
 */
#include "LED.h"
static uint8_t Toggle_Flag=0;

void vidTOGGLE_Led(uint8_t LED_ID)
{
	if(LOW==Toggle_Flag)
	{
		DIO_Write(LED_ID,HIGH);
		Toggle_Flag=HIGH;
	}
	else
	{
		DIO_Write(LED_ID,LOW);
		Toggle_Flag=LOW;


	}
}
void vidLED_On(uint8_t LED_ID)
{
	DIO_Write(LED_ID,HIGH);

}
void vidLED_off(uint8_t LED_ID)
{
	DIO_Write(LED_ID,LOW);

}


