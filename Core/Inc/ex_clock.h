/*
 * ex_clock.h
 *
 *  Created on: Oct 7, 2025
 *      Author: Dell
 */

#ifndef INC_EX_CLOCK_H_
#define INC_EX_CLOCK_H_

#include "main.h"
#include "ex_clock.h"

enum clock_state {
	INIT,
	LED0,
	LED1,
	LED2,
	LED3
};

void updateClockBuffer();
void display7SEG(uint8_t digit);
void enable7SEG(uint8_t num);
void Ex_run();

#endif /* INC_EX_CLOCK_H_ */
