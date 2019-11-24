/*
 * BCM_Proj.c
 *
 * Created: 11/17/2019 4:54:45 PM
 * Author : Ammar Shahin
 */ 

#include "Typedefs.h"
#include "BCM.h"
#include "Bcm_PBCfg.h"
#include "Tmu.h"
#include "Tmu_Lcfg.h"
#include "Interrupts.h"
#include "Led.h"
#include <avr/sleep.h>

void Task1(void)
{
	Led_Tog(LED0);
}

void Task2(void)
{
	Led_Tog(LED1);
}

void Task3(void)
{

}

void Task4(void)
{
	
}


#define ARRAY_SIZE 1000
uint8 arr[ARRAY_SIZE];

int main(void)
{
	uint16 index;
	for(index = 0; index < ARRAY_SIZE ; index++)
	{
		arr[index] = 'M';
	}
	
	Led_Init(LED0);
	Led_Init(LED1);
	Led_Init(LED2);
	Led_Init(LED3);
	
	BCM_Init(Task1);
	/* Setting the Tx_Buffer to send 120 char */
	BCM_Tx_SetupBuffer(arr,ARRAY_SIZE);
	
	uint8 job_ID0,job_ID1,job_ID2;
	TMU_Init(&tmu_cfg_s);
	/* Start 3 Tmu Jobs */
	TMU_Start_Timer(10,JOB_PERIODIC,Task2,&job_ID0);
	TMU_Start_Timer(100,JOB_PERIODIC,Task3,&job_ID1);
	TMU_Start_Timer(500,JOB_PERIODIC,Task4,&job_ID2);
	
	set_sleep_mode(SLEEP_MODE_IDLE);
    while (TRUE) 
    {
		/* Led3 to indicate the Full Time of the while loop */
		Led_On(LED3); 
		
		/* Led2 to indicate the time of the Dispatchers */
		Led_On(LED2);
		BCM_TxDispatcher();
		TMU_Dispatcher();
		Led_Off(LED2);
		
		/* Start the sleep mode */
		sleep_mode();
		Led_Off(LED3);
    }
	return 0;
}
