#include "stm32f1xx_hal.h"
#include "Reception_RF.h"


void initialiser_input_PWM_TIM(TIM_HandleTypeDef *timer_config)
{
	
	//Déclararion des variables pour configurer les channel et le trigger pour la pwm input
	TIM_IC_InitTypeDef Ch2_Config;
	TIM_IC_InitTypeDef Ch1_Config;
	TIM_SlaveConfigTypeDef Tim_trigger;
	
	
	//Configuration du Trigger en Reset Mode et en TI1FP1 selected
	Tim_trigger.SlaveMode =TIM_SLAVEMODE_RESET;
	Tim_trigger.InputTrigger = TIM_TS_TI1FP1;
	
	Ch1_Config.ICPolarity = TIM_ICPOLARITY_RISING;
	Ch2_Config.ICPolarity = TIM_ICPOLARITY_FALLING;
	Ch1_Config.ICPrescaler = TIM_ICPSC_DIV1;
	Ch2_Config.ICPrescaler = TIM_ICPSC_DIV1;
	Ch2_Config.ICSelection = TIM_ICSELECTION_INDIRECTTI;
	
	HAL_TIM_IC_MspInit(timer_config);
	__HAL_RCC_TIM4_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	HAL_TIM_IC_Init(timer_config);
	HAL_TIM_IC_ConfigChannel(timer_config, &Ch1_Config, TIM_CHANNEL_1);
	HAL_TIM_IC_ConfigChannel(timer_config, &Ch2_Config ,TIM_CHANNEL_2);
	HAL_TIM_SlaveConfigSynchronization(timer_config, &Tim_trigger);
	HAL_TIM_IC_Start(timer_config, TIM_CHANNEL_1);
	HAL_TIM_IC_Start(timer_config, TIM_CHANNEL_2);
	

}
