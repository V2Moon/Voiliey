#ifndef __Control_Moteur_CC_H_
#define __Control_Moteur_CC_H_


void init_config_moteur(GPIO_InitTypeDef * Pin_vitesse, GPIO_InitTypeDef * Pin_Sens, TIM_HandleTypeDef * timer, TIM_OC_InitTypeDef * tim_OC);
void set_sens_moteur(GPIO_InitTypeDef * Pin_Sens, GPIO_PinState sens);
void set_vitesse_moteur(float rapport_cyclique, TIM_OC_InitTypeDef * tim_OC, TIM_HandleTypeDef *timer);


#endif
