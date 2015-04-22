#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <firebird/lcd.h>
#include <firebird/motor.h>
#include <firebird/sensor.h>
#include <firebird/timer.h>

#define PI 3.141592

#define SHARP_THRESHOLD 200 // mm
#define IR_THRESHOLD 128

void LED_bargraph_config (void)
{
     DDRJ = 0xFF;  //PORT J is configured as output
     PORTJ = 0x00; //Output is set to 0
}

void init_devices()
{
    cli();
    lcd_init();
    motor_init();
    sensor_init();
    timer_init();
    LED_bargraph_config();
    sei();
}


int main()
{
    init_devices();

    lcd_print(1,1,120,3);

    motion_set(FORWARD);

    velocity(128,128);

    while(1){
        lcd_print(2,1,sharp_distance(SHARP_N),5);   
    }

    return 0;
}
