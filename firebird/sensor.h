#include "common.h"
#include <math.h> //included to support power function

#ifndef _SENSOR_H
#define _SENSOR_H 1

#define IR_W 4
#define IR_NW 5
#define IR_N 6
#define IR_NE 7
#define IR_E 8

#define WL_3 1
#define WL_2 2
#define WL_1 3

#define SHARP_W 9
#define SHARP_NW 10
#define SHARP_N 11
#define SHARP_NE 12
#define SHARP_E 13

unsigned char sharp, distance, adc_reading;
unsigned int value;
float BATT_Voltage, BATT_V;

void adc_pin_config (void);
void adc_init();
void sensor_init();

unsigned int ADC_Conversion(unsigned char Ch);
unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading);
void print_sensor(char row, char column,unsigned char channel);

unsigned int sharp_distance(unsigned char channel);
unsigned int IR_reading(unsigned char channel);

#endif
