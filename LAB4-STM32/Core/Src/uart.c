/*
 * uart.c
 *
 *  Created on: Dec 6, 2022
 *      Author: Phuc
 */

#include "uart.h"

UART_HandleTypeDef huart2;

void uart_init() {
	sprintf(tx_buffer, "INITIALIZING UART...\r\n");
	HAL_UART_Transmit(&huart2, (void*)tx_buffer, sizeof(tx_buffer), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_buffer, 1);
}

void uart_print_str(char str[]) {
	sprintf(tx_buffer, "");
	rx_buffer = "";
	HAL_UART_Transmit(&huart2, (void*)tx_buffer, sprintf(tx_buffer, "%s\r\n", str), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_buffer, 1);
}

void uart_print_with_num(char str[], uint32_t num) {
	sprintf(tx_buffer, "");
	rx_buffer = "";
	char numBuffer[50];
	//Convert number to string
	sprintf(numBuffer, "%d", num);
	sprintf(tx_buffer, "%s%s\r\n", str, numBuffer);
	HAL_UART_Transmit(&huart2, (void*)tx_buffer, strlen(tx_buffer), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_buffer, 1);
}

