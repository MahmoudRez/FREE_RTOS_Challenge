/*
 * LED.h
 *
 *  Created on: Nov 15, 2019
 *      Author: alx
 */

#ifndef LED_H_
#define LED_H_
#include "DIO.h"

#define LED1 16
#define LED2 17
#define LED3 18
#define LED4 19
extern void vidLED_Init(void);
extern void vidTOGGLE_Led(uint8 LED_ID);
extern void vidLED_On(uint8 LED_ID);
extern void vidLED_off(uint8 LED_ID);



#endif /* LED_H_ */
