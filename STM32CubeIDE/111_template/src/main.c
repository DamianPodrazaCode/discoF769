#include "stm32f7xx.h"
#include "stdlib.h"

#define LED1_PORT		GPIOJ
#define LED2_PORT     	GPIOJ
#define LED1_PIN 	  	GPIO_PIN_13
#define LED2_PIN    	GPIO_PIN_5

static void SystemClock_Config(void);
static void Gpio_init(void);

int main(void) {

	HAL_Init();
	SystemClock_Config();
	Gpio_init();

	while (1) {

		HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
		HAL_Delay(1000);
	}
}

void SystemClock_Config(void) { // 200MHz
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 400;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 8;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	HAL_PWREx_EnableOverDrive();
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_ClkInitStruct.ClockType =
			(RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
}

void Gpio_init(void) {
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	GPIO_InitTypeDef gpio_cfg;
	gpio_cfg.Pin = LED1_PIN | LED2_PIN;
	gpio_cfg.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(LED1_PORT, &gpio_cfg);
}

