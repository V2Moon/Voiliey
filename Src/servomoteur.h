#ifndef __SERVOMOTEUR_H_
#define __SERVOMOTEUR_H_


void initialiser_input_PWM_TIM(TIM_HandleTypeDef *timer_config);
void config_PWM (GPIO_InitTypeDef *PA8,TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer);
void gerer_pwm (float angle,TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer);
float compute_angle(int a_girouette);

#endif
