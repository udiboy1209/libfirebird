#include "common.h"

/**
 * @file lcd.h
 * @author Meet Udeshi
 * @brief Set of functions to control and print to LCD screen
 *
 * You can print @c char , @c string and  @c int on the LCD.
 * You can also change and reset cursor position.
 */


#ifndef _LCD_H
#define _LCD_H 1

#define RS 0 
#define RW 1
#define EN 2
#define lcd_port PORTC

#define sbit(reg,bit)	reg |= (1<<bit)
#define cbit(reg,bit)	reg &= ~(1<<bit)

void lcd_reset_4bit();

/**
 * @brief Initializes the port and send init commands to LCD 
 *
 * PORTC is set to output except for 3<su>rd</su> bit
 * All PORTC bit values set to 0 , and init commands sent to LCD
 *
 * <b>Should necessarily be called before using any other function</b>
 */
void lcd_init();

/**
 * @brief send command to LCD to be executed
 */
void lcd_wr_command(unsigned char);

/**
 * @brief write a single character at current cursor position
 */
void lcd_wr_char(char);

/**
 * @brief reset LCD and set cursor position to (1,1)
 */
void lcd_home();

/**
 * @brief move cursor to position
 *
 * @param row row position beginning from 1 to 2
 * @param column column position beginning from 1 to 16
 *
 * Cursor is moved to the position (@p row,@p column)
 */
void lcd_cursor(char, char);

/**
 * @brief print integer on LCD to specified number of digits
 *
 * @param row row position
 * @param column column position
 * @param i integer to be printed
 * @param n number of digits of integer to print
 *
 * First @p n digits of the integer @p i are printed at position (@p row, @p column)
 * For eg.
 * @code
 *  lcd_print(1,1,1543,2)
 * @endcode
 * will print first 2 digits of 1543 at (1,1)
 */
void lcd_print(char, char, unsigned int, int);

/**
 * @brief print string of characters
 *
 * @param string string of characters to be printed
 *
 */
void lcd_string(char*);

unsigned int temp;
unsigned int unit;
unsigned int tens;
unsigned int hundred;
unsigned int thousand;
unsigned int million;

int i;

#endif
