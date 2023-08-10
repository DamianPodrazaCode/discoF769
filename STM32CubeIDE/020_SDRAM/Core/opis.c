/*
 * opis.c
 *
 *  Created on: Aug 10, 2023
 *      Author: ZoMbiE
 */

#include "main.h"

// adres start 0xC0000000 - adres stop 0xc0ffffff - 128Mb, 16MB, 8M half Word, 4M Word
#define SDRAM_BANK_ADDR                 			((uint32_t)0xC0000000)
#define SDRAM_TIMEOUT     							((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1            	((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2            	((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4            	((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8            	((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL     	((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED    	((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2             	((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3             	((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD   	((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED	((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE    	((uint16_t)0x0200)

static SDRAM_HandleTypeDef hsdram1;
static FMC_SDRAM_CommandTypeDef command;

static void FMC_Init(void);
static void Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);

static void FMC_Init(void) {
	FMC_SDRAM_TimingTypeDef SdramTiming = { 0 };

	// Perform the SDRAM1 memory initialization sequence
	hsdram1.Instance = FMC_SDRAM_DEVICE;
	// hsdram1.Init

	//(clock and chip enable) wybiera się otpowiednie piny, i automatycznie wybiera się bank
	hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
	//manual Column addressing 256 | A[7:0]
	hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
	// manual Row addressing 4K A[11:0]
	hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
	// szerokość szyny danych
	hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
	// manual, ilość banków
	hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	//(CAS latency) jeżeli jest możliwość to wybieramy odpowiednią CL i doniej dopasowujemy czasy wg manuala
	hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
	// zabezpieczenie zapisu
	hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	//dzielnik taktowania pamięci, 200Mhz/2 = 100MHz dla SDRAM
	hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;

	hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;

	hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;

	// SdramTiming
	// Trzeba odszukać odpowiednie wartości z manuala
	// Zegar dla sdram to 100MHz, wskazany przez dzielnik w hsdram1.Init.CASLatency
	// obliczamy czas trwania i cykla zegara, 1/100Mhz = 10ns, wszystkie dane poniżej są w cylklach

	// TMRD: 2 Clock cycles - LOAD MODE REGISTER command to ACTIVE or REFRESH command
	SdramTiming.LoadToActiveDelay = 2;
	// TXSR: min=67ns - Exit SELF REFRESH-to-ACTIVE command
	// obliczmy 67ns/10ns = 6.7, zaokrąglamy i podajemy w cyklach
	SdramTiming.ExitSelfRefreshDelay = 7;
	// TRAS: min=42ns max=120ns - ACTIVE-to-PRECHARGE command
	// 42ns/10ns = 4.2, zaokrąglamy i podajemy w cyklach
	SdramTiming.SelfRefreshTime = 4;
	// TRC: min=60ns - ACTIVE-to-ACTIVE command period
	// 60ns/10ns = 6, zaokrąglamy i podajemy w cyklach
	SdramTiming.RowCycleDelay = 6;
	// TWR: 1clk+7ns = 10ns+7ns = 17ns - WRITE recovery time
	// 17ns/10ns = 1.7, zaokrąglamy i podajemy w cyklach
	SdramTiming.WriteRecoveryTime = 2;
	// TRP: 18ns - PRECHARGE command period
	// 18ns/10ns = 1.8, zaokrąglamy i podajemy w cyklach
	SdramTiming.RPDelay = 2;
	// TRCD: 18ns - ACTIVE-to-READ or WRITE delay
	// 18ns to prawie 2 cykle i tu zaokrąglamy w góre i podajemy w cyklach
	SdramTiming.RCDDelay = 2;

	HAL_SDRAM_Init(&hsdram1, &SdramTiming);

	Initialization_Sequence(&hsdram1, &command);
}

// inicjalizacja pamięci SDRAM, każda pamięć ma swój rodzaj inicjalizacji, ale wszystkie są do siebie bardzo podobne
static void Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command) {
	__IO uint32_t tmpmrd = 0;
	// Configure a clock configuration enable command
	Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

	// Insert 100 us minimum delay. Inserted delay is equal to 1 ms due to systick time base unit (ms)
	HAL_Delay(1);

	// Configure a PALL (precharge all) command
	Command->CommandMode = FMC_SDRAM_CMD_PALL;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

	// Configure a Auto-Refresh command
	Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command->AutoRefreshNumber = 8;
	Command->ModeRegisterDefinition = 0;
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

	// Program the external memory mode register
	tmpmrd = (uint32_t)
	SDRAM_MODEREG_BURST_LENGTH_1 |
	SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
	SDRAM_MODEREG_CAS_LATENCY_2 |
	SDRAM_MODEREG_OPERATING_MODE_STANDARD |
	SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
	Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = tmpmrd;
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

	// Set the refresh rate counter, (15.62 us x Freq) - 20, Set the device refresh counter
	hsdram->Instance->SDRTR |= ((uint32_t) ((1292) << 1));
}