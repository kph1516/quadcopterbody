/*
 * quadcopterbody.c
 *
 * Created: 7/22/2012 9:40:29 PM
 *  Author: Steve and Kyle
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void UsartInit(void);
void Data_decoding(void);
//variable

char val="C";
char rxData[4]={'e','e','e','e'};
int count=0;
int xpos,ypos;


int main(void)
{
    while(1)
    {
		UsartInit();
		
    }
}
    
void UsartInit(void)
{
	//set baud rate to 9600;
	USARTF0_BAUDCTRLB = 204;
	USARTF0_BAUDCTRLA = 245;
	USARTF0_CTRLA = 0x30; //receive interrupt
	USARTF0_CTRLB = 0x18; //enable tx rx
	USARTF0_CTRLC = 0x03; // set it to asynchronous&8bits

	PORTF_DIR |= 0x08;
	//PORTF_OUT = 0x08;
	PORTF.DIRCLR = 0x04;
	//set PMIC high level enable
	PMIC.CTRL |= 0x04;
}

ISR(USARTF0_RXC_vect)
{       
	val = USARTF0_DATA;
	while(val /= 'B'){
		if (val=='A')
			count=0;
		else
			count=count++;
		rxData[count]=val;
	}

	PORTE_DIR |= 0x01;	
	PORTE.OUTSET |= 0x01;
	_delay_ms(100);
	PORTE.OUTSET |= 0x01;
}
void Data_decoding(void){
	ypos=(int)rxData[0];
	ypos|=(int)rxData[1]<<8;	
	xpos=(int)rxData[2];
	xpos|=(int)rxData[3]<<8;
	}