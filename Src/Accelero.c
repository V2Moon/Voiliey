/*
  ******************************************************************************
  * File Name          : Accelero.c
  * Description        : This file manages the accelerometer
	* Author 						 : Louna Vielfaure
	*	Last update				 : 20/11/18
  ******************************************************************************
	*	Reste à faire : * Configurer l'accéléromètre
	*									* Réaliser la conversion des données
	*									* Mettre en forme tout joliment
	*
	*	Pbs : * Comment gérér les variables avec l'interruption (doivent être
	*					passées en global ?) : ADC_Accel_Handle
	*
	*
	******************************************************************************
*/

#include "stm32f1xx_hal.h"
#include "Accelero.h"


//Les valeurs reçues par capt
int X=0;
int Y=0;

//Valeur max de l'angle de roulis en VOLT
int High_Treeshold=10; //(+45°)
int Low_Treeshold=10;	 //(-45°)

//La valeur de l'angle de roulis en degrés
int angle=0;

//Les pins et broches
GPIO_TypeDef * GPIO_Accel = GPIOC;//, IN_PIN, INPUT_FLOATING};
char Accel_PINX = 10;
char Accel_PINY = 11;

uint32_t Prio_Accel = 2;


void Init_Accelero (void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
		
//Configuration de l'ADC pour lire les données du capteur	
	
	//Activer PIN de l'ADC = PINX accéléro
	GPIO_InitTypeDef GPIO_Accel_InitStruct;
  GPIO_Accel_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_Accel_InitStruct.Pull = GPIO_NOPULL;
	GPIO_Accel_InitStruct.Pin = Accel_PINX;
	HAL_GPIO_Init(GPIO_Accel, &GPIO_Accel_InitStruct);
		
	//Activer PIN de l'ADC = PINY accéléro
	GPIO_Accel_InitStruct.Pin = Accel_PINY;
	HAL_GPIO_Init(GPIO_Accel, &GPIO_Accel_InitStruct);	
	
	
	//Paramètrage du Init ADC (utilisé dans ma struct )
	ADC_InitTypeDef ADC_Accel_Init; 
	ADC_Accel_Init.DataAlign=ADC_DATAALIGN_RIGHT;
	ADC_Accel_Init.ScanConvMode = ADC_SCAN_DISABLE;
			
	//Paramètrage de la structure ADC Handle-> Utilise l'ADC_InitTypeDef
	ADC_HandleTypeDef ADC_Accel_Handle; // AAAAAAAH je le met où ???
	ADC_Accel_Handle.Instance= ADC1;
	ADC_Accel_Handle.Init = ADC_Accel_Init;	
	HAL_ADC_Init(&ADC_Accel_Handle);	
			
	//Config channel 11 ADC
	ADC_ChannelConfTypeDef ADC_Channel_Init;
	ADC_Channel_Init.Channel=ADC_CHANNEL_11;
	ADC_Channel_Init.Rank=ADC_REGULAR_RANK_11;	
	HAL_ADC_ConfigChannel(&ADC_Accel_Handle, &ADC_Channel_Init);
	
	//Config channel 10 ADC
	ADC_Channel_Init.Channel=ADC_CHANNEL_10;
	ADC_Channel_Init.Rank=ADC_REGULAR_RANK_10;	
	HAL_ADC_ConfigChannel(&ADC_Accel_Handle, &ADC_Channel_Init);
	
	//Config du watchdog
	ADC_AnalogWDGConfTypeDef ADC_WDG_Conf;
	ADC_WDG_Conf.WatchdogMode=ADC_ANALOGWATCHDOG_ALL_REG;
	ADC_WDG_Conf.HighThreshold=High_Treeshold;
	ADC_WDG_Conf.LowThreshold=Low_Treeshold;
	ADC_WDG_Conf.ITMode=ENABLE; // Lève l'IT de l'ADC quand on sort de la zone WatchDog
	HAL_ADC_AnalogWDGConfig(&ADC_Accel_Handle,&ADC_WDG_Conf);
	
//Configuration de l'IT de l'ADC lorsque l'on est à l'angle limite

	//Config NVIC de l'ADC : activation IT globale de l'ADC dans le STM32
	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
			
	//Priorité de l'IT
	HAL_NVIC_SetPriority(ADC1_2_IRQn, Prio_Accel, Prio_Accel);
	
	//Configuration de l'IT de l'ADC : Insert HAL_ADC_IRQHandler() in ADC1_IRQHandler()
	//Modifier la fonction HAL_ADC_IRQHandler pour avoir l'effet voulu quand le bon flag est levé
}


//Paramétrer le capteur de l'accéléro
void set_g_select (void)
{
//Choisi la précision du capteur
//Pas sleep 2=1, 1=0	
	
}

//Interruption sur l'ADC, pas besoin de getangle !


//		////Return l'angle de roulis
//	int get_angle (void)
//	{
//	//X=PC0 du STM32 (ADC_IN10)
//	//Y=PC1 (ADC_IN11)
//	return atan(X/Y);
//	}

//IT = changement des valeurs de l'angle roulis
//Handler = regarde si >45
