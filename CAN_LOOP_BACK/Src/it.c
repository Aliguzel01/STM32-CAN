/*
 * it.c
 *
 *  Created on: 1 Eki 2020
 *      Author: HP
 */


#include "main.h"




void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();

}



