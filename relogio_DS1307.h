/*
 * relogio_DS1307.h
 *
 * Created: 25/07/2018 21:06:52
 *  Author: Lucas Tadeu
 */ 


#ifndef RELOGIO_DS1307_H_
#define RELOGIO_DS1307_H_

#include "config_ControlMix.h"
#include <DS1307.h>

DS1307 rtc(PIN_WIRE_SDA,PIN_WIRE_SCL);

void config_DS1307();
void atualiza_ds1307(String inputString);

void config_DS1307()
{
	rtc.halt(false);
	rtc.setDOW(TUESDAY);        // Set Day-of-Week to SUNDAY
	rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
	rtc.setDate(26, 06, 2018);   // Set the date to October 3th, 2010
	rtc.setSQWRate(SQW_RATE_1);
	rtc.enableSQW(true);
	
	DEBUG.println(rtc.getDateStr());
	DEBUG.println(rtc.getTimeStr());
}

void atualiza_ds1307(String inputString)
{
	uint8_t dia_semana,hora,minuto,segundo,dia,mes;
	uint16_t ano;
	
	//60;4;01/01/2018;10:10:10
	
	dia_semana= inputString.substring(3, 1).toInt();
	dia = inputString.substring(5, 7).toInt();
	mes = inputString.substring(8, 10).toInt();
	ano = inputString.substring(11, 15).toInt();

	hora = inputString.substring(16, 18).toInt();
	minuto = inputString.substring(19, 21).toInt();
	segundo = inputString.substring(22).toInt();

	rtc.setDOW(dia_semana);
	rtc.setTime(hora, minuto, segundo);
	rtc.setDate(dia, mes, ano);
	
	DEBUG.println(rtc.getTimeStr());
	DEBUG.println(rtc.getDateStr());
	DEBUG.println(rtc.getDOWStr());
	DEBUG.println(F("DS1307 ATUALIZADO!"));
	
	
}

#endif /* RELOGIO_DS1307_H_ */