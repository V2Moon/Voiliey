#include "stm32f1xx_hal.h"
#include "servomoteur.h"
#include "gpio.h"

int compute_angle(int a_girouette) {

	int theta; //angle du bras du servomoteur
	int x = 90/105;
	if ((a_girouette > 180+45) & (a_girouette < 180-45))  {  //vent de face
		
		theta = 0 ;  //voiles rentrées
		
	}
	else if ((a_girouette > (360-30)) & (a_girouette < 30)) { //vent arrière
		
		theta = 90; 
	
	}
	else if ((a_girouette>(180+45)) & (a_girouette< (360-30))){ //vent de gauche
		
		theta = (x)*a_girouette;
		
	}
	
	else if ((a_girouette>(30)) & (a_girouette< (180-45))){  //vent de droite
		
		theta = -(x)*a_girouette;
		
	}
	
	return theta;
}




void config_PWM (GPIO_InitTypeDef *PA8,TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer) {
	
	tim_OC->OCMode =TIM_OCMODE_PWM1;
	tim_OC->Pulse =240;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	HAL_GPIO_Init(GPIOA,PA8);
	HAL_TIM_PWM_MspInit(timer);
	__HAL_RCC_TIM1_CLK_ENABLE();
	HAL_TIM_PWM_Init(timer);
	HAL_TIM_PWM_ConfigChannel(timer,tim_OC,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(timer,TIM_CHANNEL_1);
	
	
}

void gerer_pwm (int angle,TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer)  {
	
	tim_OC->Pulse =(480*angle)/90;
	
	HAL_TIM_PWM_ConfigChannel(timer,tim_OC,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(timer,TIM_CHANNEL_1);
	
	
}
