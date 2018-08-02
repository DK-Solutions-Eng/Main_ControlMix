/*
* config_ControlMix.h
*
* Created: 20/06/2018 11:58:19
*  Author: Lucas Tadeu
*/

#include "cartao_SD.h"

#ifndef CONFIG_CONTROLMIX_H_
#define CONFIG_CONTROLMIX_H_

#define RS232_TTL Serial3
#define RS232_BAUD 9600
#define RS232_CONFIG SERIAL_8N1

#define  RS485_interno Serial1
#define  RS485_interno_BAUD 19200
#define	RS485_interno_CONFIG SERIAL_8N2
#define MAX485_DE_INTERNO      41
#define MAX485_RE_NEG_INTERNO  41

#define	RS485_externo Serial2
#define	RS485_externo_CONFIG SERIAL_8N2
#define RS485_externo_BAUD 19200
#define MAX485_CONTROLE_EX      40

#define DEBUG	Serial
#define DEBUG_BAUD	57600
#define	DEBUG_CONFIG	SERIAL_8N1

void config_port();
void config_IO();

void config_port()
{
	RS232_TTL.begin(RS232_BAUD,RS232_CONFIG);
	RS232_TTL.println("RS232_TTL Configurado!");
	
	RS485_externo.begin(RS485_externo_BAUD,RS485_externo_CONFIG);
	pinMode(MAX485_CONTROLE_EX,OUTPUT);
	digitalWrite(MAX485_CONTROLE_EX,HIGH);
	RS485_externo.println("RS485 Externo Configurado!");
	digitalWrite(MAX485_CONTROLE_EX,LOW);
	
	DEBUG.begin(DEBUG_BAUD,DEBUG_CONFIG);
	DEBUG.println("Porta de Debug Configurada!");
}







#endif /* CONFIG_CONTROLMIX_H_ */