#include "UART.h"


/*=================================================================================
Autor : Carrel Nirina
Software : Keil uVision 5
Processor : STM32F103RB
===================================================================================*/
//TX PB10
//RX PB11

void init_Pin_UART3(void){
	//set TX
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	//Init TX
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	//set RX
	GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	//Init RX
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


/*
void config_UART3 (void){
	


}*/
