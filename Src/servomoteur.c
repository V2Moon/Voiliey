#include "stm32f1xx_hal.h"
#include "servomoteur.h"
#include "gpio.h"

float compute_angle(int a_girouette) {
	int a_girouette1 = a_girouette/4;
	float theta; //angle du bras du servomoteur
	float x = 90.0/105.0;
	if ((a_girouette1 > 180+45) & (a_girouette1 < 180-45))  {  //vent de face
		
		theta = 90.0 ;  //voiles rentrées
		
	}
	else if ((a_girouette1 > (360-30)) & (a_girouette1 < 30)) { //vent arrière
		
		theta = 0; 
	
	}
	else if ((a_girouette1>(180+45)) & (a_girouette1< (360-30))){ //vent de gauche
		
		theta = x*(float)(a_girouette1-(180+45));
		
	}
	
	else if ((a_girouette1>(30)) & (a_girouette1< (180-45))){  //vent de droite
		
		theta = x*(float)(a_girouette1);
		
	}
	
	return theta;
}




void config_PWM (GPIO_InitTypeDef *PA8,TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer) {
	
	tim_OC->OCMode =TIM_OCMODE_PWM1;
	tim_OC->Pulse =360;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	HAL_GPIO_Init(GPIOA,PA8);
	HAL_TIM_PWM_MspInit(timer);
	__HAL_RCC_TIM1_CLK_ENABLE();
	HAL_TIM_PWM_Init(timer);
	HAL_TIM_PWM_ConfigChannel(timer,tim_OC,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(timer,TIM_CHANNEL_1);
	HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
	HAL_TIM_PWM_Start_IT(timer, TIM_CHANNEL_1);
	
	
}

void gerer_pwm (float angle,TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer)  {
	
	tim_OC->Pulse =(int)(240+(120*angle)/90);
	
	HAL_TIM_PWM_ConfigChannel(timer,tim_OC,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(timer,TIM_CHANNEL_1);
	
	
}
