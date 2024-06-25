#include <avr/io.h>
#include "std_macros.h"

void ADC_vinit(unsigned char pinnumber)
{
	for(unsigned char bit = 0 ; bit < 3 ; bit++)
	{
		if(IS_BIT_SET(pinnumber , bit)) SET_BIT(ADMUX , bit);
		else CLR_BIT(ADMUX , bit);
	}
	
	SET_BIT(ADMUX,REFS0);              //configure VREF
	SET_BIT(ADCSRA,ADEN);             // enable ADC
	
	/* adjust ADC clock*/
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
}

unsigned short ADC_u16Read(unsigned char pinnumber)
{
	for(unsigned char bit = 0 ; bit < 3 ; bit++)
	{
		if(IS_BIT_SET(pinnumber , bit)) SET_BIT(ADMUX , bit);
		else CLR_BIT(ADMUX , bit);
	}
	
	unsigned short read_val;

	SET_BIT(ADCSRA , ADSC);
	while(IS_BIT_SET(ADCSRA , ADSC));   //stay in your position till ADSC become 0
	
	read_val = (ADCL);
	read_val |= (ADCH << 8);
	
	return read_val ;
}