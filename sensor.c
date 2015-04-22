#include "firebird/sensor.h"

/*
 ADC Connection:
 			  ACD CH.	PORT	Sensor
			  0			PF0		Battery Voltage
			  1			PF1		White line sensor 3
			  2			PF2		White line sensor 2
			  3			PF3		White line sensor 1
			  4			PF4		IR Proximity analog sensor 1*****
			  5			PF5		IR Proximity analog sensor 2*****
			  6			PF6		IR Proximity analog sensor 3*****
			  7			PF7		IR Proximity analog sensor 4*****
			  8			PK0		IR Proximity analog sensor 5
			  9			PK1		Sharp IR range sensor 1
			  10		PK2		Sharp IR range sensor 2
			  11		PK3		Sharp IR range sensor 3
			  12		PK4		Sharp IR range sensor 4
			  13		PK5		Sharp IR range sensor 5
			  14		PK6		Servo Pod 1
			  15		PK7		Servo Pod 2
 */
//ADC pin configuration
void adc_pin_config (void)
{
    DDRF = 0x00; //set PORTF direction as input
    PORTF = 0x00; //set PORTF pins floating
    DDRK = 0x00; //set PORTK direction as input
    PORTK = 0x00; //set PORTK pins floating
}

//Function to Initialize ADC
void adc_init()
{
	ADCSRA = 0x00;
	ADCSRB = 0x00;		//MUX5 = 0
	ADMUX = 0x20;		//Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
	ACSR = 0x80;
	ADCSRA = 0x86;		//ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0
}

void sensor_init(){
    adc_pin_config();
    adc_init();
}

//This Function accepts the Channel Number and returns the corresponding Analog Value 
unsigned int ADC_Conversion(unsigned char Ch)
{
	unsigned int a;
	if(Ch>7)
	{
		ADCSRB = 0x08;
	}
	Ch = Ch & 0x07;  			
	ADMUX= 0x20| Ch;	   		
	ADCSRA = ADCSRA | 0x40;		//Set start conversion bit
	while((ADCSRA&0x10)==0);	//Wait for ADC conversion to complete
	a=ADCH;
	ADCSRA = ADCSRA|0x10; //clear ADIF (ADC Interrupt Flag) by writing 1 to it
	ADCSRB = 0x00;
	return a;
}

// This Function prints the Analog Value Of Corresponding Channel No. at required Row
// and Coloumn Location. 
void print_sensor(char row, char column,unsigned char channel)
{
	unsigned int ADC_Value = ADC_Conversion(channel);
	lcd_print(row, column, ADC_Value, 3);
}


// This Function calculates the actual distance in millimeters(mm) from the input
// analog value of Sharp Sensor. 
unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading)
{
	unsigned int distanceInt;
	distanceInt = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
	if(distanceInt>800)
	{
		distanceInt=800;
	}
	return distanceInt;
}

unsigned int sharp_distance(unsigned char channel){
    return Sharp_GP2D12_estimation(ADC_Conversion(channel));
}

unsigned int IR_reading(unsigned char channel){
    return ADC_Conversion(channel);
}
