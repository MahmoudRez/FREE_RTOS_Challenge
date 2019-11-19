/*
 * RTOS_Sprint1.c
 *
 * Created: 11/15/2019 3:16:26 PM
 * Author : M_Moawad, Mahmoud Rezk,Ahmed ELamier and Mahmoud Khaled
 */ 


#include "Sprint2_Story2.h"

void main(void)
{



	/********************Event group Creation***************/
	vidCreatAllEvents();
	/********************Mutex Creation*********************/
	vidCreateAllMutex();
	/*******************Task Creation************************/

	xTaskCreate(vidINIT_Task,"init",85,NULL,4,NULL);

	xTaskCreate(vidPB1_Task,"Push_Button1",85,NULL,3,NULL);

	xTaskCreate(vidPB2_Task,"Push_Button2",200,NULL,3,NULL);

	xTaskCreate(vidLED_Task,"LED_State",85,NULL,3,NULL);

	xTaskCreate(vidLCD_Task,"LCD",100,NULL,1,NULL);





	/*******************************************/


	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}

}



