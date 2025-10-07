/*
 * software_timer.h
 *
 *  Created on: Oct 7, 2025
 *      Author: Dell
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

void setTimer(uint8_t index, uint16_t duration);
uint8_t isTimerExpired(uint8_t index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
