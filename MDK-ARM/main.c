#include "girouette.h"
#include "stm32f1xx_hal.h"

int main(void) {
	interface_encoder_mode();
	
	int a;
	
	while(1) {
		a = lire_angle();
	}
}