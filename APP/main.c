/*
 * main.c
 *
 *  Created on: Jan 29, 2021
 *      Author: Kishk
 *
 */

#include "../Services/STD_TYPES.h"
#include "../Services/BIT_MATHS.h"
#include "util/delay.h"
#include "../MCAL/01-DIO/DIO_interface.h"
#include "../MCAL/04- ADC/ADC_interface.h"
#include "../HAL/04- CLCD/CLCD_interface.h"


void Warning(void);
void LED_ON(void);
void LED_OFF(void);

u8 u8flag = 2;
int main(void) {
	ADC_voidInit();
	CLCD_voidInit();
	u16 LOC_u16Result =0;
	u8  LOC_u16Temp	=0;

	DIO_enumSetPinDirection(DIO_PORTB_PIN0,DIO_OUTPUT);
	DIO_enumSetPinDirection(DIO_PORTB_PIN1,DIO_OUTPUT);
	DIO_enumSetPinDirection(DIO_PORTB_PIN2,DIO_OUTPUT);
	DIO_enumSetPinDirection(DIO_PORTB_PIN3,DIO_OUTPUT);
	while (1) {
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
		CLCD_voidSendString((u8 *) "Temperature:");
		LOC_u16Result = ((u32)ADC_u16GETChannelResult(ADC_ADC0_PORTA_PIN0)*5000)/1023;
		LOC_u16Temp = LOC_u16Result / 10;
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_13);
		CLCD_voidSendString((u8 *) "   ");
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_13);
		CLCD_voidSendNumber(LOC_u16Temp);
		CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
		CLCD_voidSendString((u8 *) "LDR:");
		LOC_u16Result = ((u32)ADC_u16GETChannelResult(ADC_ADC1_PORTA_PIN1)*5000)/1023;
		CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_5);
		CLCD_voidSendString((u8 *) "    ");
		CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_5);
		CLCD_voidSendNumber(LOC_u16Result);
		_delay_ms(50);

		if(LOC_u16Temp >= 50){
			Warning();
		}
		else{
			DIO_enumSetPinValue(DIO_PORTB_PIN1, DIO_LOW);
			DIO_enumSetPinValue(DIO_PORTB_PIN0, DIO_LOW);
			DIO_enumSetPinValue(DIO_PORTB_PIN3, DIO_LOW);
		}

		if(LOC_u16Result < 700 && u8flag != 0){
			LED_OFF();
		}
		else if(LOC_u16Result > 700 && u8flag != 1){
			LED_ON();
		}

	}

}

void Warning(void){
	CLCD_voidClearDisplay();
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_3);
	CLCD_voidSendString((u8 *) "Warning!!!");
	DIO_enumSetPinValue(DIO_PORTB_PIN1, DIO_HIGH);
	DIO_enumSetPinValue(DIO_PORTB_PIN0, DIO_HIGH);
	DIO_enumSetPinValue(DIO_PORTB_PIN3, DIO_HIGH);
	_delay_ms(100);
}


void LED_OFF(void){
	u8flag = 0;
	CLCD_voidClearDisplay();
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_3);
	CLCD_voidSendString((u8 *) "LIGHT OFF");
	DIO_enumSetPinValue(DIO_PORTB_PIN2, DIO_HIGH);
	_delay_ms(100);
}

void LED_ON(void){
	u8flag = 1;
	CLCD_voidClearDisplay();
	CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_3);
	CLCD_voidSendString((u8 *) "LIGHT ON");
	DIO_enumSetPinValue(DIO_PORTB_PIN2, DIO_LOW);
	_delay_ms(100);

}



