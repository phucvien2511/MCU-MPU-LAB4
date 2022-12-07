/*
 * uart.h
 *
 *  Created on: Dec 6, 2022
 *      Author: Phuc
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "global.h"
#include <stdio.h>
#include <stdint.h>

extern UART_HandleTypeDef huart2;

uint32_t rx_buffer;
uint32_t tx_buffer[10];

void uart_init();
void uart_print_str(char str[]);
void uart_print_with_num(char str[], uint32_t num);

#endif /* INC_UART_H_ */
