#include "stm32f1xx_hal.h"
#include "girouette.h"
#include "gpio.h"

void interface_encoder_mode() {

	TIM3->CCER  &= ~(0x0011) ; /*mise à 0 de CC1E et CC2E pour pouvoir écrire dans CC1S et CC2S */
	
	
	TIM3->CCMR1 &= ~(0x0300) ; /* mise à zéro des bits 8 et 9 qui corresponde à CC2S */
	TIM3->CCMR1 |= (0x01<<8) ; /*on met dans le CC2S "01" pour connecter TI2 */
	
	TIM3->CCMR1 &= ~0x0003 ; /* mise à zéro des bits 0 et 1 qui corresponde à CC1S */
	TIM3->CCMR1 |= (0x01) ; /*on met dans le CC1S "01" pour connecter TI1 */
	
	
	TIM3->CCER  |= 0x0011 ; /*mise à 1 de CC1E et CC2E pour enable la capture*/
	
	
	TIM3->CCER  &= ~0x0002 ; /*CC1P à 0 = capture on rising edges pour IC1*/
	
	TIM3->CCMR1 &= ~0x00F0 ; /* IC1F = 0000 pour clock pas divisée*/ 
	
	TIM3->CCER  &= ~0x0020 ; /*CC2P à 0 = capture on rising edges pour IC2*/
	
	TIM3->CCMR1 &= ~0xF000 ;	/* IC2F = 0000 pour clock pas divisée*/
	
	
	TIM3->SMCR &= ~0x0007 ; /*mise à 0 des bits 0 à 2*/
	TIM3->SMCR |= 0x0003 ; /*SMS = "011" -> Counter counts up/down on both
										TI1FP1 and TI2FP2 edges si les deux entrées n'arrivent pas en meme temps */
	



	TIM3->CR1 |= 0x0001 ; // CEN =1 activer le counter
}

int lire_angle() {
	
	return TIM3->CNT ;
	
}
