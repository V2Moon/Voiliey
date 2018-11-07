#ifndef _MYGPIO_H_
#define _MYGPIO_H_

#include "stm32f10x.h"

typedef struct
{
 GPIO_TypeDef * GPIO ;
 char GPIO_Pin;
 char GPIO_Techno;
}GPIO_Struct_TypeDef;

//Selon CNF et MOD
//GPIO_Techno de type :
#define In_Floating (4)
#define In_PullDown (8) //ODR=0
#define In_PullUp (8) //ODR=1
#define In_Analog (0)
#define Out_Ppull (1)
#define Out_OD (6)

void GPIO_Init( GPIO_Struct_TypeDef * GPIOStructPtr); // configuration d'une pin
int GPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin); // renvoie 0 ou autre chose différent de 0
void GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin); // met 3,3V sur la pin et le GPIO souhaités
void GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin); // met 0V sur la pin et le GPIO souhaités


#endif
