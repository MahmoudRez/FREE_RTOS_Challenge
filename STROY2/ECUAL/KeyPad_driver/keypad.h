/******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.h
 *
 * Description: header file of Keypad static code
 *
 * Author: Mahmoud Rezk
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../mcal/DIO_driver/DIO.h"
#include "../../mcal/Utils/registers.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 3
#define NO_KEY_PRESSED 20
#define KEYPAD_DONE 26

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(uint8* Pressed_Key);

#endif /* KEYPAD_H_ */
