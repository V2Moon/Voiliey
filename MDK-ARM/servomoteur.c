#include "stm32f1xx_hal.h"
#include "servomoteur.h"
#include "gpio.h"

int control_angle(int a_girouette) {

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

