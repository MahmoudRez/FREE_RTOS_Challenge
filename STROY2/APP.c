/*
 * APP.c
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
#include "App.h"
/************************PROTOTYPES*************************/
/*Task Description: System Initialization Task
 * Prototype:void vTaskCode_Init(void * COPY_pvParameters);
 * i/p:    Void Pointer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/

static void vTaskCode_Init(void * COPY_pvParameters);

/*Task Description: Display Data Get from The Keypad on LCD
 * Prototype:void vTackCode_LCD_Display(void * COPY_pvParameters);
 * i/p:    Void Pointer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
static void vTackCode_LCD_Display(void * COPY_pvParameters);

/*TASK DESCRIPTION:a task to Get which key is pressed
 * on Keypad
 * PROTOTYPE:void vTaskGetKey(void * COPY_pvParameters);
 * I/P: NULL
 * O/P: NULL
 * I-O/P: NULL
 * Return: NULL
 * */
static void vTaskGetKey(void * COPY_pvParameters);

/*Task Description: Get the Password which user
 *                  enter it through the keypad and check if
 *                   this password correct or wrong
 * Prototype:static uint8 PassWord_Check(uint8* COPY_Password_Buffer);
 * i/p: a Pointer to Password Buffer which user Entered it
 *      COPY_Password_Buffer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
static uint8 PassWord_Check(uint8* COPY_Password_Buffer);


/************************Global Variables*************************/


static volatile uint8 g_u8InitFlag = UNINITIALIZED;
static volatile uint8 g_u8KeyPad_Enable = ENABLE;
static volatile uint8 g_u8LCD_charDisplayRequest=NO_REQUEST;
static volatile uint8 g_u8LCD_Data_Display=0;
static volatile uint8 const g_u8Password[PASSWORD_SIZE]={1,2,3,6,5,4};


/****************************************************************/


/*vTasksCreationInit
 * Prototype:void vTasksCreationInit(void);
 * Description:This Function creates init task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTasksCreationInit( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned=xTaskCreate
			(
					vTaskCode_Init, /*Pointer to Function*/
					"Init_Task",    /*Task Name*/
					configMINIMAL_STACK_SIZE,/*Stack Size for This Task*/
					NULL,
					4,/*Task Priority*/
					&xHandle /*Task Handler*/
			);
}
/*vTasksCreationInit
 * Prototype:void vTasksCreation_Lcd_Display( void )
 * Description:This Function creates LCD Display task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTasksCreation_Lcd_Display( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned=xTaskCreate(
			vTackCode_LCD_Display,
			"LCD_Display",
			configMINIMAL_STACK_SIZE,
			NULL,
			3,
			&xHandle
	);
}
/*vTasksCreationInit
 * Prototype:void vTasksCreationInit(void);
 * Description:This Function creates Keypad Get Key task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTasksCreationKeypad( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
			vTaskGetKey,       /* Function that implements the task. */
			NULL,          /* Text name for the task. */
			configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
			( void * ) 1,    /* Parameter passed into the task. */
			3,/* Priority at which the task is created. */
			&xHandle );      /* Used to pass out the created task's handle. */

}
/*Task Description: System Initialization Task
 * Prototype:void vTaskCode_Init(void * COPY_pvParameters);
 * i/p:    Void Pointer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
static void vTaskCode_Init(void * COPY_pvParameters)
{
	static uint8 LOC_DIO_Init_Status = UNINITIALIZED;
	static uint8 LOC_LCD_Init_Status = UNINITIALIZED;

	while(1)
	{
		if(UNINITIALIZED == g_u8InitFlag)
		{
			if(INITIALIZED != LOC_DIO_Init_Status)
			{
				DIO_init();
				LOC_DIO_Init_Status = INITIALIZED;
			}

			if(INITIALIZED != LOC_LCD_Init_Status)
			{
				LOC_LCD_Init_Status = LCD_init(LCD_ptrConfig);
				if(LCD_DONE == LOC_LCD_Init_Status)
				{
					LOC_LCD_Init_Status = INITIALIZED;
					g_u8InitFlag = INITIALIZED;
				}
			}
		}
		if(UNINITIALIZED == g_u8InitFlag)
		{
			vTaskDelay(1);
		}
		else if(INITIALIZED == g_u8InitFlag)
		{
			vTaskSuspend(NULL);
		}
	}
}
/*Task Description: Display Data Get from The Keypad on LCD
 * Prototype:void vTackCode_LCD_Display(void * COPY_pvParameters);
 * i/p:    Void Pointer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
static void vTackCode_LCD_Display(void * COPY_pvParameters)
{
	static volatile uint8 LOC_Task_Flag=0;
	static volatile uint8 LOC_LCD_DispFuncStatus=0;
	static volatile uint8 LOC_DispData;
	static volatile uint8 LOC_LCD_Flag=FREE;
	static const uint8 LOC_DispChar[10] = {
			'0',
			'1',
			'2',
			'3',
			'4',
			'5',
			'6',
			'7',
			'8',
			'9',
	};

	while(1)
	{
		if(INITIALIZED == g_u8InitFlag )
		{
			if(REQUESTED == g_u8LCD_charDisplayRequest )
			{
				g_u8KeyPad_Enable = DISABLE;
				if(FREE == LOC_LCD_Flag )
				{
					if(9 > g_u8LCD_Data_Display )
					{
						LOC_DispData = g_u8LCD_Data_Display;
					}
					else
					{
						LOC_DispData = 9;
					}
					LOC_LCD_Flag =RUNNING;
				}

				if(9 > LOC_DispData )
				{
					LOC_LCD_DispFuncStatus = LCD_displayChar(LOC_DispChar[g_u8LCD_Data_Display]);
				}
				else if(CLEAR == LOC_DispData )
				{
					LOC_LCD_DispFuncStatus = LCD_clear();
				}
				else if(PASSWORD_NOTMATCH== LOC_DispData )
				{
					LOC_LCD_DispFuncStatus = LCD_displayString("WRONG PASSWORD");
				}
				else if(CORRECT_PASSWORD== LOC_DispData )
				{
					LOC_LCD_DispFuncStatus = LCD_displayString("CORRECT PASSWORD");
				}

				if( LCD_STR_COMPELET== LOC_LCD_DispFuncStatus )
				{
					g_u8LCD_Data_Display=9;
					LOC_LCD_Flag=FREE;
					LOC_Task_Flag=1;
				}
				else if(LCD_DONE == LOC_LCD_DispFuncStatus )
				{
					if(9 < g_u8LCD_Data_Display )
					{
						LOC_DispData = g_u8LCD_Data_Display;
					}
					else
					{
						g_u8LCD_charDisplayRequest =NO_REQUEST;
						LOC_LCD_Flag=FREE;
						g_u8KeyPad_Enable = ENABLE;
					}
				}
			}
		}

		if(0 != LOC_Task_Flag )
		{
			LOC_Task_Flag = 0;
			vTaskDelay(2000);
		}
		else
		{
			vTaskDelay(1);
		}
	}
}
/*Task Description: Get the Password which user
 *                  enter it through the keypad and check if
 *                   this password correct or wrong
 * Prototype:static uint8 PassWord_Check(uint8* COPY_Password_Buffer);
 * i/p: a Pointer to Password Buffer which user Entered it
 *      COPY_Password_Buffer
 * o/p:    NULL
 * i-o/p:  NULL
 * return: NULL:*/
static uint8 PassWord_Check(uint8* COPY_Password_Buffer)
{
	uint8 LOC_RetValue=CORRECT_PASSWORD;
	uint8 LOC_Digit_Number;

	for(LOC_Digit_Number=0 ; LOC_Digit_Number<6 ; LOC_Digit_Number++)
	{
		if(COPY_Password_Buffer[LOC_Digit_Number] != g_u8Password[LOC_Digit_Number])
		{
			LOC_RetValue = PASSWORD_NOTMATCH;
		}
	}

	return LOC_RetValue;
}
/*TASK DESCRIPTION:a task to Get which key is pressed
 * on Keypad
 * PROTOTYPE:void vTaskGetKey(void * COPY_pvParameters);
 * I/P: NULL
 * O/P: NULL
 * I-O/P: NULL
 * Return: NULL
 * */
static void vTaskGetKey(void * COPY_pvParameters)
{
	static uint8 LOC_Task_Periodicity=30;
	static uint8 LOC_GET_KEY;
	static uint8 LOC_u8GetKey_Status;
	static uint8 LOC_PreviousKey = NO_KEY_PRESSED;
	static uint8 LOC_passWordBuffer[LCD_LINE_SIZE];
	static uint8 LOC_NumOfDigits=0;

	while(1)
	{
		LOC_u8GetKey_Status = KeyPad_getPressedKey(&LOC_GET_KEY);
		if((LOC_u8GetKey_Status == KEYPAD_DONE) && (g_u8KeyPad_Enable==ENABLE))
		{
			if(LOC_PreviousKey != LOC_GET_KEY)
			{
				LOC_PreviousKey = LOC_GET_KEY;

				if(LOC_GET_KEY == ENTER)
				{
					if(LOC_NumOfDigits != PASSWORD_SIZE)
					{
						g_u8LCD_Data_Display = PASSWORD_NOTMATCH;
					}
					else
					{
						LOC_u8GetKey_Status = PassWord_Check(LOC_passWordBuffer);
						if(LOC_u8GetKey_Status == PASSWORD_NOTMATCH)
						{
							g_u8LCD_Data_Display = PASSWORD_NOTMATCH;
						}
						else if(LOC_u8GetKey_Status == CORRECT_PASSWORD)
						{
							g_u8LCD_Data_Display = CORRECT_PASSWORD;
						}
					}
					LOC_NumOfDigits=0;
				}
				else if(LOC_GET_KEY == CLEAR)
				{
					g_u8LCD_Data_Display=LOC_GET_KEY;
					LOC_NumOfDigits=0;
				}
				else
				{
					g_u8LCD_Data_Display=LOC_GET_KEY;
					LOC_passWordBuffer[LOC_NumOfDigits]=LOC_GET_KEY;
					LOC_NumOfDigits++;

				}
				g_u8LCD_charDisplayRequest=REQUESTED;

			}
		}
		else if(LOC_u8GetKey_Status == NO_KEY_PRESSED)
		{
			LOC_PreviousKey = NO_KEY_PRESSED;
		}
		vTaskDelay(LOC_Task_Periodicity);
	}
}

