#ifndef _CHECK_BATTERY_H_
#define _CHECK_BATTERY_H_

#include <stdio.h>
#include "stm32f1xx_hal.h"
/*=================================================================================
Autor : Carrel Nirina
Software : Keil uVision 5
Processor : STM32F103RB
===================================================================================*/

void init_PC2(void);
void init_ADC1(ADC_HandleTypeDef* ADC_InitHandle);
unsigned int read_battery(ADC_HandleTypeDef* hadc);

#endif
