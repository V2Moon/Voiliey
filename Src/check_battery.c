#include "check_battery.h"


/*=================================================================================
Autor : Carrel Nirina
Software : Keil uVision 5
Processor : STM32F103RB
===================================================================================*/

/*=================================================================================
Programs necessary for monitoring the battery of the project Voilier. When 
the level of the battery is low, a message is send with RF sender.
===================================================================================*/
unsigned int valeur;
unsigned int size;
unsigned int pourcentage;
char data[21];
/*=================================================================================
Initialize the GPIOC 2 in Analog input
===================================================================================*/
void init_PC2(void){
	//set GPIOC 2
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	//Init GPIOC 2
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/*=================================================================================
Initialize the ADC1 channel 12
===================================================================================*/
void init_ADC1(ADC_HandleTypeDef* ADC_InitHandle){
	//init ADC
	init_PC2();
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ContinuousConvMode = ENABLE;
	ADC_InitStruct.NbrOfConversion = 16;
	//init Channel 12
	ADC_ChannelConfTypeDef ADC_InitChannel;
	ADC_InitChannel.Channel = ADC_CHANNEL_12;
	ADC_InitChannel.Rank = ADC_REGULAR_RANK_1;
	//init Handle ADC
	ADC_InitHandle->Instance = ADC1;
	ADC_InitHandle->Init = ADC_InitStruct;
	//CALL HAL FUNCTION FOR INIT
	HAL_ADC_Init(ADC_InitHandle);
	HAL_ADC_ConfigChannel(ADC_InitHandle,&ADC_InitChannel);
}

/*=================================================================================
Read the level of the battery
===================================================================================*/
unsigned int read_battery(ADC_HandleTypeDef* hadc){
	uint32_t a;
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, 5);
	a = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
	return a;
}

/*=================================================================================
Send the level of the battery
===================================================================================*/
void transmit_lvl_battery(ADC_HandleTypeDef* hadc, UART_HandleTypeDef* huart){
	
	valeur = read_battery(hadc);
	if(valeur >= VMAX) 
		pourcentage = 100;
	else if (valeur >= VMAX*0.75)
			pourcentage = 75;
	else if (valeur >= VMAX*0.5)
			pourcentage = 50;
	else if (valeur >= VMAX*0.25)
			pourcentage = 25;	
	else
		pourcentage = 0;
	size = sprintf(data,"Battery level : %u\n",pourcentage);
	HAL_UART_Transmit(huart,(unsigned char*)data,size,10);
}




