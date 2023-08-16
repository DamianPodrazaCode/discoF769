#include "stm32f7xx.h"
#include "stdlib.h"

#define LED1_PORT		GPIOJ
#define LED2_PORT     	GPIOJ
#define LED1_PIN 	  	GPIO_PIN_13
#define LED2_PIN    	GPIO_PIN_5

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define SDRAM_DEVICE_ADDR  ((uint32_t)0xC0000000)
#define SDRAM_DEVICE_SIZE  ((uint32_t)0x1000000)
#define SDRAM_BANK_COUNT   (SDRAM_DEVICE_SIZE/0x100)

static void SystemClock_Config(void);
static void Gpio_init(void);
static void Fmc_init(void);
static void Sdram_init(void);

int main(void) {

	HAL_Init();
	SystemClock_Config();
	Gpio_init();
	Fmc_init();
	Sdram_init();

	struct Test_ERR {
		uint32_t addr_err[0x100];
		uint8_t ram_err[0x100];
		uint8_t sdram_err[0x100];
	};

	volatile uint32_t test_ok = 0; //zmienna w której będzie wynik testu
	struct Test_ERR test_err;

	// uzupełnienie randomem małego bloku na stosie
	uint8_t tab[0x100];
	srand(HAL_GetTick());
	for (int i = 0; i < 0x100; i++) {
		tab[i] = rand() % 0x100;
	}

	// zapełnienie całej sdram powtarzanymi blokami
	for (int j = 0; j < SDRAM_BANK_COUNT; j++)
		for (int i = 0; i < 0x100; i++) {
			*(__IO uint8_t*) (SDRAM_DEVICE_ADDR + (j * 0x100) + (1 * i)) = tab[i];
		}

	// porównanie pamięci
	for (int j = 0; j < SDRAM_BANK_COUNT; j++)
		for (int i = 0; i < 0x100; i++) {
			if ((*(__IO uint8_t*) (SDRAM_DEVICE_ADDR + (j * 0x100) + (1 * i))) != tab[i]) {
				test_err.addr_err[test_ok] = (SDRAM_DEVICE_ADDR + (j * 0x100) + (1 * i));
				test_err.sdram_err[test_ok] = *(__IO uint8_t*) (SDRAM_DEVICE_ADDR + (j * 0x100) + (1 * i));
				test_err.ram_err[test_ok] = tab[i];
				test_ok++;
			}
		}

	while (1) {
		HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
		HAL_Delay(1000);
	}
}

void SystemClock_Config(void) {
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

void Fmc_init(void) {
	__HAL_RCC_FMC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();

	GPIO_InitTypeDef gpio_cfg;
	gpio_cfg.Mode = GPIO_MODE_AF_PP;
	gpio_cfg.Pull = GPIO_PULLUP;
	gpio_cfg.Speed = GPIO_SPEED_HIGH;
	gpio_cfg.Alternate = GPIO_AF12_FMC;

	gpio_cfg.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &gpio_cfg);

	gpio_cfg.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
			| GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &gpio_cfg);

	gpio_cfg.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11
			| GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOF, &gpio_cfg);

	gpio_cfg.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOG, &gpio_cfg);

	gpio_cfg.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
			| GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOH, &gpio_cfg);

	gpio_cfg.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
			| GPIO_PIN_9 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOI, &gpio_cfg);
}

SDRAM_HandleTypeDef sdramHandle;
void Sdram_init(void) {

	sdramHandle.Instance = FMC_SDRAM_DEVICE;
	sdramHandle.Init.SDBank = FMC_SDRAM_BANK1;
	sdramHandle.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
	sdramHandle.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
	sdramHandle.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
	sdramHandle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	sdramHandle.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
	sdramHandle.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	sdramHandle.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
	sdramHandle.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
	sdramHandle.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
	FMC_SDRAM_TimingTypeDef Timing;
	Timing.LoadToActiveDelay = 2;
	Timing.ExitSelfRefreshDelay = 7;
	Timing.SelfRefreshTime = 4;
	Timing.RowCycleDelay = 7;
	Timing.WriteRecoveryTime = 2;
	Timing.RPDelay = 2;
	Timing.RCDDelay = 2;
	HAL_SDRAM_Init(&sdramHandle, &Timing);

	static FMC_SDRAM_CommandTypeDef Command = { 0 };
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;

	Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, 100);
	HAL_Delay(1);

	Command.CommandMode = FMC_SDRAM_CMD_PALL;
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, 100);

	Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.AutoRefreshNumber = 8;
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, 100);

	Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command.ModeRegisterDefinition =
			SDRAM_MODEREG_BURST_LENGTH_1 | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL | SDRAM_MODEREG_CAS_LATENCY_3
					| SDRAM_MODEREG_OPERATING_MODE_STANDARD | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, 100);

	HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 1539);
}