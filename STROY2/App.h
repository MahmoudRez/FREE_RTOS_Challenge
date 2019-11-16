/*
 * App.h
 *	Sprint1-->> Story2
 *	Requirements:
 *	Use an existing RTOS project to write a simple lock program with the following requirements:
 *  AGILE_REQ1:
 *              < Two tasks with user defined periodicities >
 *  AGILE_REQ2:
 *              < A task dedicated to read input from keypad >
 *  AGILE_REQ3:
 *              < A task dedicated to output on LCD >
 *  AGILE_REQ4:
 *              < User shall be able to enter any number from (0 -> 6)
 *               on keypad and numbers entered are displayed on LCD >
 *  AGILE_REQ5:
 *            < Keypad shall contain an erase button, When
 *             pressed the LCD is cleared and cursor returns home >
 *  AGILE_REQ6:
 *             < Keypad shall contain an enter button, When pressed
 *              the LCD is cleared and cursor returns home >
 *  AGILE_REQ7:
 *             < User shall enter a 6 digit code and press enter
 *             and if the code is correct LCD shall display
 *             “Correct password” for two seconds and
 *             switch to accept new inputs from user >
 *  Created on: Nov 15, 2019
 *      Author: Mahmoud Rezk & Mahmoud Yaakoub
 */

#ifndef APP_H_
#define APP_H_
/******************Libraries Includes*****************/
#include "FREE_RTOS_Files/FreeRTOS.h"
#include "FREE_RTOS_Files/task.h"
#include "mcal/DIO_driver/DIO.h"
#include "ECUAL/LCD_driver/LCD.h"
#include "ECUAL/KeyPad_driver/keypad.h"
/*******************Configurations*******************/
#define DISABLE 0
#define ENABLE 1
#define UNINITIALIZED 0
#define INITIALIZED 1
#define PASSWORD_NOTMATCH 10
#define CORRECT_PASSWORD 11
#define LCD_LINE_SIZE 16
#define PASSWORD_SIZE 6
#define ENTER 7
#define CLEAR 9
#define NO_REQUEST 0
#define REQUESTED 1
#define FREE 0
#define RUNNING 1
/********************Prototypes************************/

/*Task Description: System Initialization Task
 * Prototype:void vTaskCode_Init(void * COPY_pvParameters);
 * i/p:    Void Pointer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
extern void vTasksCreationInit( void );
/*vTasksCreationInit
 * Prototype:void vTasksCreation_Lcd_Display( void )
 * Description:This Function creates LCD Display task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
extern void vTasksCreation_Lcd_Display( void );
/*vTasksCreationInit
 * Prototype:void vTasksCreationInit(void);
 * Description:This Function creates Keypad Get Key task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
extern void vTasksCreationKeypad( void );



#endif /* APP_H_ */
