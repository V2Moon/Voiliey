#include "girouette.h"
#include "stm32f1xx_hal.h"

int test(void) {
	interface_encoder_mode();
	
	int a;
	
	while(1) {
		a = lire_angle();
	}
}