#ifndef _UART_H_
#define _UART_H_

#include <stdio.h>
#include "stm32f1xx_hal.h"
#include <string.h>

void init_Pin_UART1(void);
void config_UART1 (UART_HandleTypeDef* UART_Handle);


#endif
