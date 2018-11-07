#include "stm32f1xx_hal.h"
#include "Accelero.h"
//#include "MyGPIO.h"

//Le PIN pour accéléro - X
//GPIO_Struct_TypeDef *AcceleroGPIOX;
//AcceleroGPIOX[1] = GPIOC;//, IN_PIN, INPUT_FLOATING};
//AcceleroGPIOX[2] = 10;

//GPIO_Struct_TypeDef *AcceleroGPIOY;
//AcceleroGPIOY[1] = GPIOC;//, IN_PIN, INPUT_FLOATING};
//AcceleroGPIOY[2] = 11;

//Activer horloge locale des 2 ADC
void init_Accelero (void)
{
	//GPIO_Init(AcceleroGPIO);

}

void config_ADC_IN10 () // IN 11 à faire aussi
{
	//Clock
	
}


//Paramétrer le capteur
void set_g_select (void)
{
//Choisi la précision du capteur
//Pas sleep 2=1, 1=0	
	
}

//Return l'angle de roulis
int get_angle (void)
{
	//X=PC0 (ADC_IN10)
	//Y=PC1 (ADC_IN11)
	return atan(X/Y);
}


//Configuration d'une IT (faire avec une structure)
void initNVIC (void)
{

}
//NVIC + Périph + handler ou tout écrire à la main ?
//IT = changement des valeurs de l'angle roulis
//Handler = regarde si >45