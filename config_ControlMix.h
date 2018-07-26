/*
* config_ControlMix.h
*
* Created: 20/06/2018 11:58:19
*  Author: Lucas Tadeu
*/

#include "cartao_SD.h"


DS1307 rtc(PIN_WIRE_SDA,PIN_WIRE_SCL);

#ifndef CONFIG_CONTROLMIX_H_
#define CONFIG_CONTROLMIX_H_

#define RS232_TTL Serial3
#define RS232_BAUD 19200
#define RS232_CONFIG SERIAL_8N1

#define	RS485_externo Serial2
#define	RS485_externo_CONFIG SERIAL_8N1
#define RS485_externo_BAUD 19200
#define MAX485_CONTROLE_EX      40

#define DEBUG	Serial
#define DEBUG_BAUD	9600
#define	DEBUG_CONFIG	SERIAL_8N1

void config_port();
void config_IO();
void config_IHM();

void config_port()
{
	RS232_TTL.begin(RS232_BAUD,RS232_CONFIG);
	RS232_TTL.println("RS232_TTL Configurado!");
	
	RS485_externo.begin(RS485_externo_BAUD,RS485_externo_CONFIG);
	pinMode(MAX485_CONTROLE_EX,OUTPUT);
	digitalWrite(MAX485_CONTROLE_EX,HIGH);
	RS485_externo.println("RS485 Externo Configurado!");
	digitalWrite(MAX485_CONTROLE_EX,LOW);
	
	DEBUG.begin(19200,SERIAL_8N1);
	DEBUG.println("Porta de Debug Configurada!");
}







#endif /* CONFIG_CONTROLMIX_H_ */