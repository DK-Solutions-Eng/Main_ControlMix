/*
indicador_aeph.h

Created: 20/06/2018 11:05:21
Author: Lucas Tadeu
*/

#ifndef INDICADOR_AEPH_H_
#define INDICADOR_AEPH_H_

#include <ModbusMaster.h>

#define  RS485_interno Serial1
#define  RS485_interno_BAUD 19200
#define	RS485_interno_CONFIG SERIAL_8N2
#define MAX485_DE_INTERNO      41
#define MAX485_RE_NEG_INTERNO  41

ModbusMaster RS485_INT;

String unidade="KG";

bool peso_bruto;

void preTransmission_RS485_interno()
{
	digitalWrite(MAX485_RE_NEG_INTERNO, 1);
	digitalWrite(MAX485_DE_INTERNO, 1);
}

void postTransmission_RS485_interno()
{
	digitalWrite(MAX485_RE_NEG_INTERNO, 0);
	digitalWrite(MAX485_DE_INTERNO, 0);
}

void config_modbus(uint8_t addr);
String get_peso(uint8_t addr);
String get_tara(uint8_t addr);
String remote_zero(uint8_t addr);
String remote_tara(uint8_t addr);
String remote_destara(uint8_t addr);
String remote_impressao(uint8_t addr);


/*
*** CONFIGURA��O DO MODBUS
*/
void config_modbus_indicador(byte addr_int)
{
	//pinMode(40,OUTPUT);
	pinMode(MAX485_DE_INTERNO, OUTPUT);

	RS485_interno.begin(RS485_interno_BAUD, RS485_interno_CONFIG);
	//RS485_externo.begin(RS485_externo_BAUD,RS485_externo_CONFIG);

	RS485_INT.begin(addr_int, RS485_interno);
	//RS485_EXT.begin(addr_ext,RS485_externo);

	RS485_INT.preTransmission(preTransmission_RS485_interno);
	RS485_INT.postTransmission(postTransmission_RS485_interno);

	//RS485_EXT.preTransmission(preTransmission_RS485_externo);
	//RS485_EXT.postTransmission(postTransmission_RS485_externo);
}

/*
*** LE O PESO DO INDICADOR
*/
String get_peso(uint8_t addr)
{
	config_modbus_indicador(addr);
	String string_peso;
	uint8_t result;
	uint16_t data[2];
	float peso;
	uint8_t status;
	bool tipo_peso, peso_negativo, saturacao, sobrecarga;
	float multiplicador;

	result = RS485_INT.readHoldingRegisters(addr, 2);

	for (char j = 0; j < 2; j++)
	{
		data[j] = RS485_INT.getResponseBuffer(j);
	}


	status = highByte(data[0]);

	#pragma region VERIFICACAO DE PESO LIQUIDO E PESO BRUTO

	if ((status & 0b10000000) == 0x80)
	{
		tipo_peso = 1;	//peso bruto
		peso_bruto=tipo_peso;
	}
	if ((status & 0b10000000) == 0)
	{
		tipo_peso = 0;	//peso liquido
		peso_bruto=tipo_peso;
	}
	#pragma endregion


	#pragma region VERIFICACAO PESO NEGATIVO

	if ((status & 0b00001000) == 0x08)
	{
		peso_negativo = 1;
	}
	if ((status & 0b00001000) == 0)
	{
		peso_negativo = 0;
	}
	#pragma endregion VERIFICACAO PESO NEGATIVO


	#pragma region VERIFICACAO DE SOBRECARGA

	if ((status & 0b01000000) == 0x40)
	{
		sobrecarga  = 1;
	}
	if ((status & 0b01000000) == 0)
	{
		sobrecarga = 0;
	}

	#pragma endregion


	#pragma region VERIFICACAO DE SATURACAO

	if ((status & 0b00100000) == 0x20)
	{
		saturacao = 1;
	}
	if ((status & 0b00100000) == 0)
	{
		saturacao = 0;
	}

	#pragma endregion


	#pragma region POSICAO PONTO DECIMAL

	switch ((status & 0b00000111))
	{
		case 0:
		multiplicador = 1.0;
		break;

		case 1:
		multiplicador = 0.1;
		break;

		case 2:
		multiplicador = 0.01;
		break;

		case 3:
		multiplicador = 0.001;
		break;

		case 4:
		multiplicador = 0.0001;
		break;

		default:
		multiplicador = 1.0;
		break;
	}

	#pragma endregion POSICAO PONTO DECIMAL


	switch (peso_negativo)
	{
		case 0:
		peso = ((lowByte(data[0]) * 65536) + (highByte(data[1]) * 256) + lowByte(data[1])) * multiplicador * (1.0);
		break;

		case 1:
		peso = ((lowByte(data[0]) * 65536) + (highByte(data[1]) * 256) + lowByte(data[1])) * multiplicador * (-1.0);
		break;

		default:
		break;
	}


	//peso=((lowByte(data[0])*65536)+(highByte(data[1])*256)+lowByte(data[1]))*0.01;

	if (sobrecarga == 1)
	{

		string_peso = "SOBRE";

	}
	else if (saturacao == 1)
	{

		string_peso = "SATURADO";
	}
	else
	{

		switch (tipo_peso)
		{
			case 0:
			string_peso = String(peso, 3) + " " + unidade /*+ "L"*/;
			break;

			case 1:
			string_peso = String(peso, 3) + " " + unidade /*+ "B"*/;
			break;

			default:
			string_peso = "N/A";
			break;
		}

	}

	return string_peso;
}

String get_tara(uint8_t addr)
{
	config_modbus_indicador(addr);
	String string_tara;
	uint8_t result;
	uint16_t data[2];
	float peso;
	uint8_t status;
	float multiplicador;

	result = RS485_INT.readHoldingRegisters(0x000C, 2);

	for (char j = 0; j < 2; j++)
	{
		data[j] = RS485_INT.getResponseBuffer(j);
	}

	status = highByte(data[0]);

	switch ((status & 0b00000111))
	{
		case 0:
		multiplicador = 1.0;
		break;

		case 1:
		multiplicador = 0.1;
		break;

		case 2:
		multiplicador = 0.01;
		break;

		case 3:
		multiplicador = 0.001;
		break;

		case 4:
		multiplicador = 0.0001;
		break;

		default:
		multiplicador = 1.0;
		break;
	}

	peso = ((lowByte(data[0]) * 65536) + (highByte(data[1]) * 256) + lowByte(data[1])) * multiplicador * (1.0);

	string_tara = "T" + String(peso, 4);

	return string_tara;

}

String remote_zero(uint8_t addr)
{

	config_modbus_indicador(addr);
	String zero_remoto;
	uint8_t result;
	uint16_t data[2];

	result = RS485_INT.writeSingleRegister(0x0002, 0x0002); //comando escrita de registrador

	for (char j = 0; j < 1; j++)
	{
		data[j] = RS485_INT.getResponseBuffer(j);
	}

	zero_remoto=String(highByte(data[0]))+String(lowByte(data[0]))+(highByte(data[1]))+String(lowByte(data[1]));

	return zero_remoto;

}

String remote_tara(uint8_t addr)
{

	config_modbus_indicador(addr);
	String tara_remoto;
	uint8_t result;
	uint16_t data[2];

	result = RS485_INT.writeSingleRegister(0x0002, 0x0001); //comando escrita de registrador

	for (char j = 0; j < 2; j++)
	{
		data[j] = RS485_INT.getResponseBuffer(j);
	}

	tara_remoto=String(highByte(data[0]))+String(lowByte(data[0]))+(highByte(data[1]))+String(lowByte(data[1]));

	return tara_remoto;

}

String remote_destara(uint8_t addr)
{

	config_modbus_indicador(addr);
	String destara_remoto;
	uint8_t result;
	uint16_t data[2];

	result = RS485_INT.writeSingleRegister(0x0002, 0x0003); //comando escrita de registrador

	for (char j = 0; j < 2; j++)
	{
		data[j] = RS485_INT.getResponseBuffer(j);
	}

	destara_remoto=String(highByte(data[0]))+String(lowByte(data[0]))+(highByte(data[1]))+String(lowByte(data[1]));

	return destara_remoto;

}

String remote_impressao(uint8_t addr)
{
	config_modbus_indicador(addr);
	String impressao_remoto;
	uint8_t result;
	uint16_t data[2];

	result = RS485_INT.writeSingleRegister(0x0002, 0x0004); //comando escrita de registrador

	for (char j = 0; j < 2; j++)
	{
		data[j] = RS485_INT.getResponseBuffer(j);
	}

	impressao_remoto=String(highByte(data[0]))+String(lowByte(data[0]))+(highByte(data[1]))+String(lowByte(data[1]));

	return impressao_remoto;
}



#endif /* INDICADOR_AEPH_H_ */
