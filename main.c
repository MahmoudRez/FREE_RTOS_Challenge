#include "FreeRTOS.h"
#include "task.h"
#include "LED.h"
#include "INFO_LCD.h"
#include "keypad.h"


                    /*Functions Prototype*/
/*vTasksCreationInit
 * Prototype:void vTasksCreationInit(void);
 * Description:This Function creates init task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTasksCreationInit(void);
/*vTaskCode_Init
 * Prototype:void vTaskCode_Init(void * pvParameters);
 * Description:Init Task Code for Initialization of the system.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTaskCode_Init(void * pvParameters);
/*vTasksCreation_LED_Toggle
 * Prototype:void vTasksCreation_LED_Toggle( void );
 * Description:create Toggle Led Task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTasksCreation_LED_Toggle( void );
/*vTaskCode_Toggle
 * Prototype:void vTaskCode_Toggle( void * pvParameters );
 * Description:Task Code for toggling a LED every 1000msec
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTaskCode_Toggle( void * pvParameters );

void main(void)
{
		/*Create Init task which Initialize DIO
		 * and Led Deriver in it
		 * */
		vTasksCreationInit( );
		/*Create Toggle led task which Toggle Led Every
		 * specific time Which User Determine based
		 * on his design */
		vTasksCreation_LED_Toggle();
		/* Start Scheduler */
		vTaskStartScheduler();


	while(1)
	{

	}
}


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


/*vTaskCode_Init
 * Prototype:void vTaskCode_Init(void * pvParameters);
 * Description:Init Task Code for Initialization of the system.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTaskCode_Init(void * pvParameters)
{
	static uint8 LCD_init_Flag=LCD_UNINTAILIZED;
	static uint8 LED_init_Flag=0;
	static uint8 KBD_init_Flag=PENDING;
	for(;;)
	{
		if(0==LED_init_Flag)
		{
			vidLED_Init();
			LED_init_Flag=1;
		}
		else
		{
			if(LCD_UNINTAILIZED==LCD_init_Flag)
			{
				DIO_Init();
				LCD_init_Flag=LCD_init();
				vTaskDelay(2);
			}
			else
			{
				if(PENDING==KBD_init_Flag)
				{
					KBD_init_Flag=KEYPAD_Init();
				}
				else
				{
					vTaskSuspend(NULL);
				}

			}
		}
	}
}

/*vTasksCreation_LED_Toggle
 * Prototype:void vTasksCreation_LED_Toggle( void );
 * Description:create Toggle Led Task.
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTasksCreation_LED_Toggle( void )
{
BaseType_t xReturned;
TaskHandle_t xHandle = NULL;

    /* Create the task, storing the handle. */
xReturned=xTaskCreate(
			vTaskCode_Toggle,
			"Toggle_Led",
			configMINIMAL_STACK_SIZE,
			NULL,
			3,
			&xHandle
	);
}

/*vTaskCode_Toggle
 * Prototype:void vTaskCode_Toggle( void * pvParameters );
 * Description:Task Code for toggling a LED every 1000msec
 * i/p:   NULL
 * o/p:   NULL
 * i-o/p: NULL
 * return:NULL
 * */
void vTaskCode_Toggle( void * pvParameters )
{
	/* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. */
	//configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	for( ;; )
	{
		/*if(LCD_init_Flag==LCD_Finished)
		{*/
			vidTOGGLE_Led(LED1);
			vTaskDelay(1000);
		//}

	}
}
