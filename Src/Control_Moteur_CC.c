#include "stm32f1xx_hal.h"
#include "Control_Moteur_CC.h"

void init_config_moteur(GPIO_InitTypeDef * Pin_vitesse, GPIO_InitTypeDef * Pin_Sens, TIM_HandleTypeDef *timer)
{

	TIM_OC_InitTypeDef tim_OC;
	tim_OC.OCMode = TIM_OCMODE_PWM1;
	tim_OC.Pulse = 359;
	
		__HAL_RCC_GPIOA_CLK_ENABLE();
	
	HAL_GPIO_Init(GPIOA, Pin_vitesse);
	//HAL_GPIO_Init(GPIOA, Pin_Sens);
	HAL_TIM_PWM_MspInit(timer);
	__HAL_RCC_TIM2_CLK_ENABLE();
	HAL_TIM_PWM_Init(timer);
	HAL_TIM_PWM_ConfigChannel(timer, &tim_OC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(timer, TIM_CHANNEL_2);
	
}

void set_sens_moteur()
{
	
}

void set_vitesse_moteur()
{
	
}