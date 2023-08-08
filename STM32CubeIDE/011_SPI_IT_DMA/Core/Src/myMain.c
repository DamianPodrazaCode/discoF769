/*
 * myMain.c
 *
 *  Created on: Aug 7, 2023
 *      Author: ZoMbiE
 */

#include "myMain.h"

extern SPI_HandleTypeDef hspi2;

void setup() {
}

void loop() {
	char pData[] = "test test!!!";
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
	HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 12, 100);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
	//HAL_Delay(1);
}
