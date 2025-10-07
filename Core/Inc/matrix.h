/*
 * matrix.h
 *
 *  Created on: Oct 7, 2025
 *      Author: Dell
 */

#ifndef INC_MATRIX_H_
#define INC_MATRIX_H_

#include "main.h"
#include "software_timer.h"

extern uint8_t index_led_matrix;

extern uint8_t matrix_buffer[8];

void enableRow(uint8_t row);
void displayRow(uint8_t matrix_buffer);
void updateLEDMatrix(uint8_t index);
void displayMatrix();
void Ex_run();

#endif /* INC_MATRIX_H_ */
