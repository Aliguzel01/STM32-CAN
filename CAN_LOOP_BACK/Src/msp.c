/*
 * msp.c
 *
 *  Created on: 1 Eki 2020
 *      Author: HP
 */

#include "main.h"

  void HAL_MspInit(void)
{
   // Burada düþük seviyeli iþlemciye özgü baþlangýçlar yapacaðýz.
	  // 1. Arm cortex mx iþlemcisinin öncelikli gruplamasýný ayarlayýn
	  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	  // 2. Arm cortex mx iþlemcisinin gerekli sistem istisnalarýný etkinleþtirin
	  SCB->SHCSR |= 0X7 << 16; //usg fault ,memoryfault  and bus fault system exceptions.

	  // 3. sistem istisnalarý için önceliði yapýlandýrýn
	  HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	  HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	  HAL_NVIC_SetPriority(UsageFault_IRQn ,0,0);

}




 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
  {
 	 GPIO_InitTypeDef gpio_uart;
 	 // burada düþük seviyeli inits yapacaðýz. USART2 çevre birimi

 	 // 1. USART2 çevre birimi ve GPIOA çevre birimi için saati etkinleþtirin
 	 __HAL_RCC_USART2_CLK_ENABLE();
 	 __HAL_RCC_GPIOA_CLK_ENABLE();
 	 // 2. Pin muxing yapýlandýrmalarýný yapýn
 	 gpio_uart.Pin=GPIO_PIN_2;
 	 gpio_uart.Mode=GPIO_MODE_AF_PP;
 	 gpio_uart.Pull=GPIO_PULLUP;
 	 gpio_uart.Alternate=GPIO_AF7_USART2;//UART2_TX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);

 	 gpio_uart.Pin=GPIO_PIN_3;//UART2_RX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);
 	 // 3. IRQ'yu etkinleþtirin ve önceliði ayarlayýn (NVIC ayarlarý)
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
