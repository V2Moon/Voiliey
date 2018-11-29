#include "stm32f10x.h"
#include "MyGPIO.h"

void GPIO_Init( GPIO_Struct_TypeDef* GPIOStructPtr) // configuration d'une pin
{
	if(GPIOStructPtr->GPIO_Pin<8)
	{ 
		GPIOStructPtr->GPIO->CRL &= ~(0xF << (4*GPIOStructPtr->GPIO_Pin));//Mettre tout à 0 sur le pin
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Techno << (4*GPIOStructPtr->GPIO_Pin));
	}
	else  //CRH pour les broches >8 (sinon on dépasse les 32 bits du registre
	{
		GPIOStructPtr->GPIO->CRH &= ~(0xF << (4*(GPIOStructPtr->GPIO_Pin-8)));
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Techno << (4*(GPIOStructPtr->GPIO_Pin-8)));		
	}	
}
int GPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin) // renvoie 0 ou autre chose différent de 0
{
	return (GPIO->IDR & (0x1 <<GPIO_Pin));
}

void GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin) // met 3,3V sur la pin et le GPIO souhaités
{
	//-> Set (peut aussi reset sur les dernier bits)
	GPIO->BSRR = (0x1<<GPIO_Pin);
}
void GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin) // met 0V sur la pin et le GPIO souhaités
{
	//-> Reset
	//Mettre un 1 dans BRR -> Met un zéro sans utiliser le "|="
	GPIO->BRR = (0x1<<GPIO_Pin); // Pourrait aussi utiliser ODR, mais il faudrait faire un masque !
}
