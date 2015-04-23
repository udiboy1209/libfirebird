#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <firebird/lcd.h>
#include <firebird/motor.h>
#include <firebird/sensor.h>

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
        forward_mm(100);

        angle_hard(45,CLOCKWISE);
    }

    return 0;
}
