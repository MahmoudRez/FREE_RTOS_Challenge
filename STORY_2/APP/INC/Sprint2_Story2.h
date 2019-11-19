/*
 * Sprint2_Story2.h
 *
 *  Created on: Nov 18, 2019
 *      Author: M_Moawad, Mahmoud Rezk,Ahmed ELamier and Mahmoud Khaled
*/
/*Application of user story two of Sprint two */
#ifndef Sprint2_Story2_H_
#define Sprint2_Story2_H_

/***************LIbraries Include*******************/

#include "FreeRTOS.h"
#include "task.h"

#include "semphr.h"
#include "event_groups.h"

#include "INFO_LCD.h"
/**********************Event Groups Configuration*****************/
#define LED_PushButton1			(1<<0)
#define LED_PushButton2			(1<<1)
#define LCD_PushButton1		    (1<<2)
#define LCD_PushButton2			(1<<3)
#define PushButtonOffLED	    (1<<4)
#define PushButtonOffLCD	    (1<<5)

/****************Push Buttons Status*******************/
#define Switch_NotPressed 0
#define Switch_Pressed 1

/*****************APIes of the application**************/

/*Task Description: System Initialization Task
 * Prototype:void vidINIT_Task(void);
 * i/p:    Void Pointer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/

/********************Task environment initialization********************/
extern void vidINIT_Task(void);
/*Task Description: First Push button Task
 * Prototype:void vidPB1_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/********************First Push button Task *****************************/
extern void vidPB1_Task(void * COPY_User_Periodicity);
/*Task Description: Secound Push button Task
 * Prototype:void vidPB1_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/********************Secound Push button Task *****************************/
extern void vidPB2_Task(void * COPY_User_Periodicity);
/*Task Description: LED Task which determine the state of Led according to
 * Push Buttons status
 * Prototype:void vidLED_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/********************LED State  Task *****************************/
extern void vidLED_Task(void * COPY_User_Periodicity);
/*Task Description: LCD Task which Monitor the state of Led according to
 * Push Buttons status.
 * Prototype:void vidLCD_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/*********LCD Task with user definition of periodicity *****************/
extern void vidLCD_Task(void * COPY_User_Periodicity);
/*Function Description: Function to create Event Group for Bush Buttons
 * to Made tasks communicate with each other syncronized
 * Prototype:void vidCreateAllMutex(void);
 * i/p:    NULL
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/*********Function to create Global mutex *****************/
extern void vidCreatAllEvents(void);
/*Function Description: Function to create Global mutex for Bush Buttons to guard
 * usage of shared resources
 * Prototype:void vidCreateAllMutex(void);
 * i/p:    NULL
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/*********Function to create Global mutex *****************/
extern void vidCreateAllMutex(void);

/********************************************************/

#endif  Sprint2_Story2_H_

