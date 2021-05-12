#ifndef _SHIFTCTRL_H
#define _SHIFTCTRL_H

#include <shiftr.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#define DEF_NUM_PINS    8
#define DEF_DATA_PIN    RPI_GPIO_P1_11
#define DEF_CLOCK_PIN   RPI_GPIO_P1_15
#define DEF_LATCH_PIN   RPI_GPIO_P1_23
#define DEF_RESET_PIN   RPI_GPIO_P1_21
#define DEF_ENABLE_PIN  RPI_GPIO_P1_19

#define DATA_PIN        0
#define CLOCK_PIN       1
#define LATCH_PIN       2
#define RESET_PIN       3
#define ENABLE_PIN      4
#define TOTAL_PINS      5

uint8_t convertNumToPin(int n);
void usage(void);
void help(void);
void die(const char *fmt, ...);

#endif /* #ifndef _SHIFTCTRL_HÄ*/
