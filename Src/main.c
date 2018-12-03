/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "Reception_RF.h"
#include "Control_Moteur_CC.h"
#include "check_battery.h"
#include "servomoteur.h"
#include "Timer_Systick.h"
#include "girouette.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
//Recepetion RF
float t_periode;
float t_cycle;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

//Moteur
float vitesse;
float rapport_cyclique;
TIM_OC_InitTypeDef tim_OC_moteur;

//Batterie
uint32_t buffalo;

//Servomoteur
TIM_OC_InitTypeDef tim_OC;
TIM_HandleTypeDef htim1;
GPIO_InitTypeDef PA8;
int angle_girouette;
float angle_theta;

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
		//pour la pin de la PWM du servomoteur
	PA8.Mode =GPIO_MODE_AF_PP;
	PA8.Pin = GPIO_PIN_8;
	PA8.Speed =GPIO_SPEED_FREQ_HIGH;
	
		//reglage du timer 1 periode de 50Hz
	htim1.Init.Prescaler =299;
	htim1.Init.Period = 4799;
	htim1.Instance = TIM1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.RepetitionCounter = 0;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
	__ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
	ADC_HandleTypeDef hadc;
	init_ADC1(&hadc);
	
	htim4.Instance = TIM4;
	/*On veut une fréquence de 50Hz, vu qu'on va surveiller un signal de période 20ms. 
	la définition temporel doit être assez grande pour qu'on puisse contrôler assez finement le moteur*/
	
	htim4.Init.Prescaler=29;
	htim4.Init.Period=47999;
	config_PWM(&PA8,&tim_OC,&htim1);
	
	
	initialiser_input_PWM_TIM(&htim4);
	
	//Configuration des pins pour le contrôle du moteur
	
	GPIO_InitTypeDef PA1;
	PA1.Mode = GPIO_MODE_AF_PP;
	PA1.Pin  = GPIO_PIN_1;
	PA1.Speed = GPIO_SPEED_FREQ_HIGH;
	
	GPIO_InitTypeDef PA2;
	PA2.Mode = GPIO_MODE_OUTPUT_PP ;
	PA2.Pin = GPIO_PIN_2;
	PA2.Speed = GPIO_SPEED_FREQ_HIGH ;
	

		
	

	htim2.Init.Prescaler = 0;
	htim2.Init.Period = 719;
	htim2.Instance = TIM2;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.RepetitionCounter=0;

	init_config_moteur(&PA1, &PA2, &htim2, &tim_OC_moteur);
	
	//Init Girouette
	connect_GPIO();
	interface_encoder_mode();
	

	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//Code pour récupérer la valeur de charge de la batterie
		//buffalo = read_battery(&hadc);
		angle_girouette = lire_angle();
		angle_theta= compute_angle(angle_girouette);
		
		
//		if (t_periode != 0)
//		{
//		rapport_cyclique = t_cycle/t_periode;

//		if (rapport_cyclique<0.1140)
//		{
//			set_sens_moteur(&PA2, GPIO_PIN_RESET);
//			vitesse = (-rapport_cyclique+0.115)/0.013;
//			tim_OC.Pulse = (int)((vitesse*720.0)-1.0);
//			
//		}
//		else if (rapport_cyclique>0.1160)
//		{
//			set_sens_moteur(&PA2, GPIO_PIN_SET);
//			vitesse = (+rapport_cyclique-0.115)/0.013;
//			tim_OC.Pulse = (int)((vitesse*720.0)-1.0);
//		}
//		else
//		{
//			tim_OC.Pulse = 0;
//		}
//		
//		//set_vitesse_moteur(rapport_cyclique,&tim_OC,&htim2);
//			
//			HAL_TIM_PWM_ConfigChannel(&htim2, &tim_OC, TIM_CHANNEL_2);
//			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
//		}
		
		
		
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
int test_girouette(void) {
	interface_encoder_mode();
	
	int a;
	
	while(1) {
		a = lire_angle();
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
