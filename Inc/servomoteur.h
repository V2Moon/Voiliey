#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include "stm32f1xx_hal.h"
#include "gpio.h"

int compute_angle(int a_girouette);
void config_PWM (GPIO_InitTypeDef *PA8,TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer);
	
#endif
