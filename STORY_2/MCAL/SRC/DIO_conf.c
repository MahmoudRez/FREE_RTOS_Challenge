/*
 * DIO_conf.c
 *
 *  Created on: Sep 20, 2019
 *      Author: abdelqader
 */

#include"DIO_conf.h"

/*Configure your pins with the same order in the enum
 { port , pin Number , Pin direction , output_value , Pullup/external resistor , initialized/not initialized }*/
	 
DIO_Conf_t DIO_Array[NUM_PINS] = {
		{PORT_A, PIN4, OUTPUT, LOW, NA, INITIALIZED },
		{PORT_A, PIN5, OUTPUT, LOW, NA, INITIALIZED },
		{PORT_A, PIN6, OUTPUT, LOW, NA, INITIALIZED },
		{PORT_A, PIN7, OUTPUT, LOW, NA, INITIALIZED },
		
		{PORT_A, PIN3, OUTPUT, LOW, NA, INITIALIZED },
		{PORT_A, PIN1, OUTPUT, LOW, NA, INITIALIZED },
		{PORT_A, PIN2, OUTPUT, LOW, NA, INITIALIZED },
/*****************PUSH Buttons Configure****************/
		{PORT_B, PIN2, INPUT, NA, EXTRES, INITIALIZED },
		{PORT_C, PIN4, INPUT, NA, EXTRES, INITIALIZED },

/********************LED  Configure*********************/

		{PORT_B, PIN4, OUTPUT, LOW, NA, INITIALIZED },
		{PORT_B, PIN5, OUTPUT, LOW, NA, INITIALIZED }


};
