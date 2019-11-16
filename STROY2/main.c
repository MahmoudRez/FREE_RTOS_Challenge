
#include "App.h"


void main(void)
{

	vTasksCreationInit();
	vTasksCreation_Lcd_Display();
	vTasksCreationKeypad();
	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
}

