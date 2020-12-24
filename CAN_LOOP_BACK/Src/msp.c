/*
 * msp.c
 *
 *  Created on: 1 Eki 2020
 *      Author: HP
 */

#include "main.h"

  void HAL_MspInit(void)
{
   // Burada d���k seviyeli i�lemciye �zg� ba�lang��lar yapaca��z.
	  // 1. Arm cortex mx i�lemcisinin �ncelikli gruplamas�n� ayarlay�n
	  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	  // 2. Arm cortex mx i�lemcisinin gerekli sistem istisnalar�n� etkinle�tirin
	  SCB->SHCSR |= 0X7 << 16; //usg fault ,memoryfault  and bus fault system exceptions.

	  // 3. sistem istisnalar� i�in �nceli�i yap�land�r�n
	  HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	  HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	  HAL_NVIC_SetPriority(UsageFault_IRQn ,0,0);

}




 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
  {
 	 GPIO_InitTypeDef gpio_uart;
 	 // burada d���k seviyeli inits yapaca��z. USART2 �evre birimi

 	 // 1. USART2 �evre birimi ve GPIOA �evre birimi i�in saati etkinle�tirin
 	 __HAL_RCC_USART2_CLK_ENABLE();
 	 __HAL_RCC_GPIOA_CLK_ENABLE();
 	 // 2. Pin muxing yap�land�rmalar�n� yap�n
 	 gpio_uart.Pin=GPIO_PIN_2;
 	 gpio_uart.Mode=GPIO_MODE_AF_PP;
 	 gpio_uart.Pull=GPIO_PULLUP;
 	 gpio_uart.Alternate=GPIO_AF7_USART2;//UART2_TX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);

 	 gpio_uart.Pin=GPIO_PIN_3;//UART2_RX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);
 	 // 3. IRQ'yu etkinle�tirin ve �nceli�i ayarlay�n (NVIC ayarlar�)
 	 HAL_NVIC_EnableIRQ (USART2_IRQn);
 	 HAL_NVIC_SetPriority (USART2_IRQn, 15 , 0 );

  }


 void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
	  GPIO_InitTypeDef GPIO_InitStruct;

   __HAL_RCC_CAN1_CLK_ENABLE();

	/**CAN1 GPIO Configuration
	PA11     ------> CAN1_RX
	PA12     ------> CAN1_TX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
