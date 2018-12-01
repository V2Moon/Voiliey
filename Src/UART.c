#include "UART.h"


/*=================================================================================
Autor : Carrel Nirina
Software : Keil uVision 5
Processor : STM32F103RB
===================================================================================*/
//TX PB10
//RX PB11

void init_Pin_UART1(void){
	//set TX
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	//Init TX
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}



void config_UART1 (UART_HandleTypeDef* UART_Handle){
	UART_InitTypeDef UART_Init;
	init_Pin_UART1();
	UART_Init.BaudRate = 9600;
	UART_Init.WordLength = UART_WORDLENGTH_8B;
	UART_Init.Parity = UART_PARITY_NONE;
	UART_Init.StopBits = UART_STOPBITS_1;
	UART_Init.Mode = UART_MODE_TX;
    UART_Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_Handle->Instance = USART1;
	UART_Handle->Init = UART_Init;
	HAL_UART_Init(UART_Handle);
}


