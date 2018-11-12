#ifndef __Control_Moteur_CC_H_
#define __Control_Moteur_CC_H_


void init_config_moteur(GPIO_InitTypeDef * Pin_vitesse, GPIO_InitTypeDef * Pin_Sens, TIM_HandleTypeDef * timer);
void set_sens_moteur();
void set_vitesse_moteur();


#endif
