/*

 * KeypadAndLcdApp.c
 *
 *  Created on: Nov 16, 2019
 *      Author: M_Moawad, Mahmoud Rezk,Ahmed ELamier and Mahmoud Khaled
 */

/*Application of user story two of Sprint two */

/*************************LIbraries Include***************************/

#include "Sprint2_Story2.h"

/******************************Global variables*********************/


static uint8_t g_Init_Flag = NOT_INITIALIZED;
EventGroupHandle_t g_xPush_Button_Flags;
SemaphoreHandle_t g_xPush_Botton_Mutex;

/****************Functions description and source code */

/*Task Description: System Initialization Task
 * Prototype:void vidINIT_Task(void);
 * i/p:    Void Pointer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/

/********************Task environment initialization********************/
void vidINIT_Task(void){

	static uint8_t LOC_DIO_Init_Status = NOT_INITIALIZED;
	Enum_LCDState LCD_State = LCD_Pending;
	while(1)
	{
		if (g_Init_Flag == NOT_INITIALIZED)
		{
			if (LOC_DIO_Init_Status != INITIALIZED)
			{
				DIO_Init();
				LOC_DIO_Init_Status = INITIALIZED;
			}
			LCD_State = LCD_init();
			if (LCD_State == LCD_Finished)
			{
				xEventGroupSetBits(g_xPush_Button_Flags,PushButtonOffLCD);
				g_Init_Flag = INITIALIZED;
				vTaskSuspend(NULL);
			}
		}
		vTaskDelay(2);
	}

}
/*Task Description: First Push button Task
 * Prototype:void vidPB1_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/********************First Push button Task *****************************/
void vidPB1_Task(void * COPY_User_Periodicity)
{
	static uint8_t LOC_Last_Switch_Status = Switch_NotPressed;
	static uint8_t LOC_Current_SwitchStatus = Switch_NotPressed;
	static uint8_t LOC_Semaphore_Taken=0;

	while(1)
	{
		/***********Guard to Check the initialization Status************/
		if(g_Init_Flag == INITIALIZED)
		{
			if(LOC_Semaphore_Taken == 0)
			{
				xSemaphoreTake(g_xPush_Botton_Mutex , portMAX_DELAY);
				LOC_Semaphore_Taken = 1;
			}
			/************************Get the status of the key Pressed or not Pressed*******************/
			DIO_Read(PUSH_BUTTON1,&LOC_Current_SwitchStatus);
			/*************************Condition of pressed key and compare
			 ************************** with last Key Status when it was unpressed**************/
			if( (LOC_Current_SwitchStatus == Switch_Pressed) && (LOC_Last_Switch_Status == Switch_NotPressed) )
			{
				LOC_Last_Switch_Status = LOC_Current_SwitchStatus;
				xEventGroupClearBits(g_xPush_Button_Flags,PushButtonOffLED|PushButtonOffLCD);
				xEventGroupSetBits(g_xPush_Button_Flags,LED_PushButton1|LCD_PushButton1);
			}
			/*************************Condition of not pressed key and compare
			 ************************** with last Key Status when it was pressed**************/
			else if( (LOC_Current_SwitchStatus == Switch_NotPressed) && (LOC_Last_Switch_Status == Switch_Pressed) )
			{
				LOC_Last_Switch_Status = LOC_Current_SwitchStatus;
				xEventGroupSetBits(g_xPush_Button_Flags,PushButtonOffLED|PushButtonOffLCD);
				xSemaphoreGive(g_xPush_Botton_Mutex);
				LOC_Semaphore_Taken=0;
			}
			/*************************Condition of not pressed key and compare
			 ********************** with last Key Status when it was unpressed**************/
			else if( (LOC_Current_SwitchStatus == Switch_NotPressed) && (LOC_Last_Switch_Status == Switch_NotPressed) )
			{
				xSemaphoreGive(g_xPush_Botton_Mutex);
				LOC_Semaphore_Taken=0;
			}
		}
		vTaskDelay(30);
	}
}
/*Task Description: Secound Push button Task
 * Prototype:void vidPB1_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/********************Secound Push button Task *****************************/

void vidPB2_Task(void * COPY_User_Periodicity)
{
	static uint8_t LOC_Last_Switch_Status = Switch_NotPressed;
	static uint8_t LOC_Current_SwitchStatus = Switch_NotPressed;
	static uint8_t LOC_Semaphore_Taken=0;

	while(1)
	{
		/***********Guard to Check the initialization Status************/
		if(g_Init_Flag == INITIALIZED)
		{
			if(LOC_Semaphore_Taken == 0)
			{
				xSemaphoreTake(g_xPush_Botton_Mutex , portMAX_DELAY);
				LOC_Semaphore_Taken = 1;
			}
			/************************Get the status of the key Pressed or not Pressed*******************/
			DIO_Read(PUSH_BUTTON1,&LOC_Current_SwitchStatus);
			/*************************Condition of pressed key and compare
			 ************************** with last Key Status when it was unpressed**************/
			if( (LOC_Current_SwitchStatus == Switch_Pressed) && (LOC_Last_Switch_Status == Switch_NotPressed) )
			{
				LOC_Last_Switch_Status = LOC_Current_SwitchStatus;
				xEventGroupClearBits(g_xPush_Button_Flags,PushButtonOffLED|PushButtonOffLCD);
				xEventGroupSetBits(g_xPush_Button_Flags,LED_PushButton1|LCD_PushButton1);
			}
			/*************************Condition of not pressed key and compare
			 ************************** with last Key Status when it was pressed**************/
			else if( (LOC_Current_SwitchStatus == Switch_NotPressed) && (LOC_Last_Switch_Status == Switch_Pressed) )
			{
				LOC_Last_Switch_Status = LOC_Current_SwitchStatus;
				xEventGroupSetBits(g_xPush_Button_Flags,PushButtonOffLED|PushButtonOffLCD);
				xSemaphoreGive(g_xPush_Botton_Mutex);
				LOC_Semaphore_Taken=0;
			}
			/*************************Condition of not pressed key and compare
			 ********************** with last Key Status when it was unpressed**************/
			else if( (LOC_Current_SwitchStatus == Switch_NotPressed) && (LOC_Last_Switch_Status == Switch_NotPressed) )
			{
				xSemaphoreGive(g_xPush_Botton_Mutex);
				LOC_Semaphore_Taken=0;
			}
		}
		vTaskDelay(30);
	}
}

/*Task Description: LED Task which determine the state of Led according to
 * Push Buttons status
 * Prototype:void vidLED_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/********************LED State  Task *****************************/
void vidLED_Task(void * COPY_User_Periodicity)
{

	static EventBits_t  LOC_LED_EventBits_Value = 0;
	while(1)
	{
		LOC_LED_EventBits_Value =  xEventGroupWaitBits(g_xPush_Button_Flags , (LED_PushButton1 | LED_PushButton2 | PushButtonOffLED) , pdFALSE , pdFALSE , portMAX_DELAY);

		LOC_LED_EventBits_Value &= ( (LED_PushButton1) | (LED_PushButton2) | (PushButtonOffLED) );
		/********Check if the First Push Button Pressed Flag to Turn Led on***********/
		if(LED_PushButton1 == LOC_LED_EventBits_Value)
		{
			vidLED_On(LED_1);
			xEventGroupClearBits(g_xPush_Button_Flags , ( LED_PushButton1) );
		}
		/********Check if the second Push Button Pressed Flag to Turn Led on***********/
		else if(LED_PushButton2==LOC_LED_EventBits_Value)
		{
			vidLED_On(LED_1);
			xEventGroupClearBits(g_xPush_Button_Flags , ( LED_PushButton2) );
		}
		/*****************Check if there is no Push Buttons Pressed flag
		 * to Turn Led on So turn Led off*********************************/

		else if(PushButtonOffLED==LOC_LED_EventBits_Value)
		{
			vidLED_off(LED_1);
			xEventGroupClearBits(g_xPush_Button_Flags , ( PushButtonOffLED ) );
		}
		else
		{

		}

		vTaskDelay(50);
	}

}
/*Task Description: LCD Task which Monitor the state of Led according to
 * Push Buttons status.
 * Prototype:void vidLCD_Task(void * COPY_User_Periodicity);
 * i/p:    Pointer to user defined aperiodicity
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/*********LCD Task with user definition of periodicity *****************/
void vidLCD_Task(void * COPY_User_Periodicity)
{

	EventBits_t  LOC_LCD_EventBits_Value = 0;
	Enum_LCDState LOC_LCD_StatusFlag = LCD_Pending;
	while(1)
	{
		/***************Check on a Event Flags which let LCD Know which Button
		 *Caused LED Turned on to monitoring the status of LED and push Buttons */
		LOC_LCD_EventBits_Value =  xEventGroupWaitBits(g_xPush_Button_Flags , (LCD_PushButton1 | LCD_PushButton2 | PushButtonOffLCD) , pdFALSE , pdFALSE , portMAX_DELAY);
		LOC_LCD_EventBits_Value &= ( (LCD_PushButton1) | (LCD_PushButton2) | (PushButtonOffLCD) );

		/************First Condition if the First push Button was responsible for
		 * turned LED on Display  "LED ON by PB 1" and clear this flag to another check */
		if(LCD_PushButton1==LOC_LCD_EventBits_Value)
		{
			LOC_LCD_StatusFlag = LCD_displayStringRowColumn("LED ON by PB 1" , 0,0);
			if (LOC_LCD_StatusFlag == LCD_Finished)
			{
				xEventGroupClearBits(g_xPush_Button_Flags , ( LCD_PushButton1 ) );
			}
			else
			{

			}
		}
		/************Second Condition if the second push Button was responsible for
		 * turned LED on Display  "LED ON by PB 2" and clear this flag to another check */
		else if(LCD_PushButton2==LOC_LCD_EventBits_Value)
		{
			LOC_LCD_StatusFlag = LCD_displayStringRowColumn("LED ON by PB 2" , 0,0);
			if (LOC_LCD_StatusFlag == LCD_Finished)
			{
				xEventGroupClearBits(g_xPush_Button_Flags , ( LCD_PushButton2 ) );
			}
			else
			{

			}
		}
		/************third Condition if there is no push Button was responsible for
		 * turned LED on so LED Turned off and LCD
		 *  Display  "LED turned off" and clear this flag to another check */
		else if(PushButtonOffLCD==LOC_LCD_EventBits_Value)
		{
			LOC_LCD_StatusFlag = LCD_displayStringRowColumn("LED turned off       " , 0,0);
			if (LOC_LCD_StatusFlag == LCD_Finished)
			{
				xEventGroupClearBits(g_xPush_Button_Flags , ( PushButtonOffLCD ) );
			}
			else
			{

			}
		}
		else
		{

		}
		vTaskDelay(2);
	}
}

/***************************************************************************/
/*Function Description: Function to create Global mutex for Bush Buttons to guard
 * usage of shared resources
 * Prototype:void vidCreateAllMutex(void);
 * i/p:    NULL
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/*********Function to create Global mutex *****************/
void vidCreateAllMutex(void)
{
	g_xPush_Botton_Mutex = xSemaphoreCreateMutex();
}
/*Function Description: Function to create Event Group for Bush Buttons
 * to Made tasks communicate with each other syncronized
 * Prototype:void vidCreateAllMutex(void);
 * i/p:    NULL
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
/*********Function to create Global mutex *****************/
void vidCreatAllEvents(void)
{
	g_xPush_Button_Flags = xEventGroupCreate();
}


