/*
 * myMain.c
 *
 *  Created on: Aug 7, 2023
 *      Author: ZoMbiE
 */

#include "myMain.h"

extern SPI_HandleTypeDef hspi2;

volatile uint8_t f_SPI_IT = 1;

char pData[] = "test test!!!";

void setup() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*) pData, 12);
}

//void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
//	if (hspi == &hspi2) {
//		f_SPI_IT = 1;
//	}
//}

void loop() {
	if (f_SPI_IT) {
//		f_SPI_IT = 0;
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
//		HAL_SPI_Transmit_IT(&hspi2, (uint8_t*) pData, 12);
	}
}
