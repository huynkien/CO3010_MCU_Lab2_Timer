/*
 * ex_clock.c
 *
 *  Created on: Oct 7, 2025
 *      Author: Dell
 */

#include "ex_clock.h"

uint8_t hour = 23;
uint8_t minute = 59;
uint8_t second = 0;

uint8_t clock_status = INIT;
uint8_t led_buffer_clock[4] = {0, 0, 0, 0};

const uint8_t SEG7_MAT[10] = {
	0X3F, // 0: a b c d e f
	0x06, // 1:   b c
	0x5B, // 2: a b   d e   g
	0x4F, // 3: a b c d     g
	0x66, // 4:   b c   f   g
	0x6D, // 5: a   c d   f g
	0x7D, // 6: a   c d e f g
	0x07, // 7: a b c
	0x7F, // 8: a b c d e f g
	0x6F  // 9: a b c d   f g
};

void display7SEG(uint8_t digit) {
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, (digit & (1u<<0)) ? RESET : SET);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, (digit & (1u<<1)) ? RESET : SET);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, (digit & (1u<<2)) ? RESET : SET);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, (digit & (1u<<3)) ? RESET : SET);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, (digit & (1u<<4)) ? RESET : SET);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, (digit & (1u<<5)) ? RESET : SET);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, (digit & (1u<<6)) ? RESET : SET);
}

void enable7SEG(uint8_t num) {
	switch (num)
	{
		case 0:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			break;
		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			break;
		case 2:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			break;
		case 3:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
			break;
		default:
			break;

	}
}

void updateClockBuffer() {
	second++;
	if (second >= 60) {
		minute++;
		second = 0;
	}
	if (minute >= 60) {
		hour++;
		minute = 0;
	}
	if (hour >= 24) {
		hour = 0;
	}
	led_buffer_clock[0] = hour / 10;
	led_buffer_clock[1] = hour % 10;
	led_buffer_clock[2] = minute / 10;
	led_buffer_clock[3] = minute % 10;
}

void Ex_run() {
	switch (clock_status)
	{
		case INIT:
			HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, SET);
			HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, SET);
			HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, SET);
			HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);
			HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
			HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);
			HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);
			clock_status = LED0;
			break;
		case LED0:
			enable7SEG(0);
			display7SEG(SEG7_MAT[led_buffer_clock[0]]);
			clock_status = LED1;
			break;
		case LED1:
			enable7SEG(1);
			display7SEG(SEG7_MAT[led_buffer_clock[1]]);
			clock_status = LED2;
			break;
		case LED2:
			enable7SEG(2);
			display7SEG(SEG7_MAT[led_buffer_clock[2]]);
			clock_status = LED3;
			break;
		case LED3:
			enable7SEG(3);
			display7SEG(SEG7_MAT[led_buffer_clock[3]]);
			clock_status = LED0;
			break;
		default:
			break;
	}
	updateClockBuffer();

}

