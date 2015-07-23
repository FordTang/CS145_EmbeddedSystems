/*
 * project4.c
 *
 * Created: 5/19/2015 4:27:02 PM
 *  Author: Ray Chou 67255516
			Ford Tang 46564602
 */ 


#include "avr.h"
#include "lcd.h"
#include <stdio.h>

char beg[17];
unsigned short result = 1;
unsigned short max=0;
unsigned short min=9999;
unsigned average=0;
unsigned long  long total=0;
int count=0;

unsigned char key_pressed(unsigned char row, unsigned char column)
{
	DDRC = 0;
	PORTC = 0;
	
	SET_BIT(PORTC, row);
	SET_BIT(DDRC, column);
	wait_avr(100);
	
	return !GET_BIT(PINC, row);

}
void get_adc()
{
		SET_BIT(ADCSRA,7);
		SET_BIT(ADCSRA,6);
		while(!(ADCSRA & (1<<ADIF)));
		result = ADC/10.23*5;
		total+=result;
		count++;
		if(result>max)
		{
			max=result;
		}
		if(result<min)
		{
			
			min=result;
		}
		average=total/count;
		//ADCSRA|=(1<<ADIF);
		CLR_BIT(ADCSRA,7);
}

int main(void)
{
	ini_lcd();
	clr_lcd();
	int ca = 0;
	int cb = 0;
	int aa=0;
	int ab=0;
	int ma=0;
	int mb=0;
	int mina=0;
	int minb=0;
	//ADMUX |= 71;
	//SET_BIT(ADMUX,6);
	//ADCSRA|=135;
	//SET_BIT(ADCSRA)
	//ADMUX=(1<<REFS0); // For Aref=AVcc;
	SET_BIT(ADMUX,6);
	//ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Prescalar div factor =128
	ADCSRA|=135;
	
	//wait_avr(50000);
	//uint8_t ch=ch&0b00000111;
	
	//ADMUX|=ch;
	//ADCSRA|=(1<<ADSC);

	//ADCSRA|=(1<<ADEN);
	
	
    while(1)
    {
        //TODO:: Please write your application code 
		pos_lcd(0,0);
		sprintf(beg,"A:Start Sampling");
		puts_lcd2(beg);
		pos_lcd(1, 0);
		sprintf(beg,"B:reset");
		puts_lcd2(beg);
		if(key_pressed(0, 7))
		{
			while(1)
			{
				if(key_pressed(1, 7))
				{
					result = 1;
					max=0;
					min=9999;
					average=0;
					total=0;
					count=0;
					clr_lcd();
					break;
				}
				get_adc();
				clr_lcd();
				pos_lcd(0, 0);
				//int a,b;
				ca = result / 100;
				cb = result % 100;
				aa=average/100;
				ab=average%100;
				ma=max/100;
				mb=max%100;
				mina=min/100;
				minb=min%100;
				sprintf(beg,"Cr:%01d.%02d Mx:%01d.%02d",ca,cb,ma,mb);//(adc/1023)*5
				puts_lcd2(beg);
				pos_lcd(1, 0);
				sprintf(beg,"Avg:%01d.%02d Mn:%01d.%02d",aa,ab,mina,minb);
				puts_lcd2(beg);
				wait_avr(500);
			}
		}
		

			
    }
}