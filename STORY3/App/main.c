

/********************** Includes ***********************/
#include "FreeRTOS.h"
#include "task.h"
#include "ExtInter.h"
#include "LED.h"
/*******************************************************/

/************** Private Local functions ****************/
static void vTasksCreation_INIT( void );
static void vTaskCreation_Toggle( void );
static void vTaskCreation_ToggleRateChange( void );
static void vTasksCreation_TimePressed( void );
static void vTasksInit(void * pvParameters );
static void vTaskToggleLED( void * pvParameters );
static void vTaskCalcTimeOfPressing(void);
static void vTaskToggleRateChange(void);
static void vButtonState(void);
/*******************************************************/

/************** Private Global Variables ****************/
static volatile uint8 g_PushedButton_PrevStateFlag=0;
static volatile uint8 g_PushedButton_CurrStateFlag=0;
static volatile uint8 g_Time_Pressed_Flag=0;
static volatile uint16 g_toggle_Rate=100;
static volatile uint8 g_toggle_Rate_Flag=0;
/*******************************************************/

int main(void)

{

	/*Tasks Initialization*/
	vTasksCreation_INIT();
	/*Create task for toggling LED*/
	vTaskCreation_Toggle();
	/*Create task for calculating Time*/
	vTasksCreation_TimePressed();
	/*Create task to change toggle rate*/
	vTaskCreation_ToggleRateChange();
	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
}
/*
 * @Function Name: vTasksCreation_INIT
 *
 * @ Function Description: function that creates the task which initializes
 * all drives needed.
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */
void vTasksCreation_INIT( void )
{
BaseType_t xReturned;
TaskHandle_t xHandle = NULL;
xReturned = xTaskCreate(vTasksInit,NULL,configMINIMAL_STACK_SIZE,(void *)1,5,&xHandle );

}

/*
 * @Function Name: vTaskCreation_Toggle
 *
 * @ Function Description:function that creates the task that toggles
 * the led with different rate.
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */
void vTaskCreation_Toggle( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(vTaskToggleLED,NULL,configMINIMAL_STACK_SIZE,(void *)1,2,&xHandle );
}
/*
 * @Function Name: vTaskCreation_ToggleRateChange
 *
 * @ Function Description: function that creates the task that
 * determines different toggling rate according to time.
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */
void vTaskCreation_ToggleRateChange( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(vTaskToggleRateChange,NULL,configMINIMAL_STACK_SIZE,(void *)1,3,&xHandle );

}

/*
 * @Function Name: vTasksCreation_TimePressed
 *
 * @ Function Description: function that creates the task which calculate
 * the time of the press on the button.
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */
void vTasksCreation_TimePressed( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(vTaskCalcTimeOfPressing,NULL,configMINIMAL_STACK_SIZE,(void *)1,4,&xHandle );

}

/*
 * @Task Name: vTasksInit
 *
 * @ Task Description: A task that initialize all drives needed and then it
 * suspends itself.
 *
 * @ Task priority: 5
 *
 * @ Task periodicity: ((((((Once))))))
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */

void vTasksInit(void * pvParameters )
{
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for( ;; )
	{
		vidLED_Init();
		INTP_vidInit();
		INTP1_vidSetCallBack(vButtonState);
		vTaskSuspend(NULL);
	}
}

/*
 * @Task Name: vTaskToggleLED
 *
 * @ Task Description: A task that toggle the led on with certain rate
 * according to time of press on the button.
 *
 * @ Task priority: 2
 *
 * @ Task periodicity: (((((((((Changeable)))))))
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */

void vTaskToggleLED( void * pvParameters )
{
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for( ;; )
	{
		if(g_PushedButton_PrevStateFlag==1 && g_toggle_Rate_Flag==1)
		{
			vidTOGGLE_Led(LED_1);
		}
		vTaskDelay(g_toggle_Rate);

	}

}
/*
 * @Task Name: vTaskCalcTimeOfPressing
 *
 * @ Task Description: A task that calculate the time of the press on a
 * button.
 *
 * @ Task priority: 4
 *
 * @ Task periodicity: 200 ms
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */

void vTaskCalcTimeOfPressing(void)
{
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for( ;; )
	{
		if(g_PushedButton_CurrStateFlag==1)
		{
			g_Time_Pressed_Flag++;
		}
		else
		{

		}
		vTaskDelay(200);
	}

}
/*
 * @Task Name: vTaskToggleRateChange
 *
 * @ Task Description: A task that monitors the pressing time on Button and
 * change toggle rate according to time.
 *
 * @ Task priority: 3
 *
 * @ Task periodicity: 200 ms
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */

void vTaskToggleRateChange(void)
{
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for( ;; )
	{
		if(g_PushedButton_CurrStateFlag==1)
		{
			if(g_Time_Pressed_Flag<10)
			{
				vidLED_off(LED_1);
			}
			else if(g_Time_Pressed_Flag>=10 && g_Time_Pressed_Flag<=20 )
			{
				g_toggle_Rate_Flag=1;
				g_toggle_Rate=400;

			}
			else if(g_Time_Pressed_Flag>20)
			{
				g_toggle_Rate_Flag=1;
				g_toggle_Rate=100;
			}
		}

		vTaskDelay(200);
	}

}

/*
 * @Function Name: vButtonState
 *
 * @ Function Description: Call back function to change button state
 * and store (current and previous states) to use them in different tasks.
 *
 * @ i/p    : Void
 * @ o/p    : Void
 * @ i-o/p  : Void
 *
 * @ return : Void
 *
 */
void vButtonState(void)
{

	if(g_PushedButton_CurrStateFlag==LOW)
	{
		g_PushedButton_CurrStateFlag=HIGH;
		g_PushedButton_PrevStateFlag=LOW;
		g_toggle_Rate_Flag=0;

	}

	else
	{
		g_PushedButton_CurrStateFlag=LOW;
		g_PushedButton_PrevStateFlag=HIGH;
		g_Time_Pressed_Flag=LOW;


	}
}
