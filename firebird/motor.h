#include "common.h"

#ifndef _MOTOR_H
#define _MOTOR_H 1

#define FORWARD 0x06
#define BACK 0x09
#define STOP 0x00
#define RIGHT 0x0A
#define SOFT_RIGHT 0x02
#define LEFT 0x05
#define SOFT_LEFT 0x04

#define CLOCKWISE 1
#define ANTICLOCKWISE -1

#define rotation_resolution 2.084076

unsigned long ShaftCountLeft; //to keep track of left position encoder
unsigned long ShaftCountRight; //to keep track of right position encoder

void motor_pin_config (void);
void timer5_init();
void motor_init (void);    

void motion_set (unsigned char Direction);
void velocity (int left_motor, int right_motor);

void left_encoder_pin_config();
void right_encoder_pin_config();
void left_position_encoder_interrupt_init(); //Interrupt 4 enable
void right_position_encoder_interrupt_init(); //Interrupt 5 enable

double angle_soft(double Degrees, int direction);
double angle_hard(double Degrees, int direction);
double forward_mm(double DistanceInMM);

#endif
