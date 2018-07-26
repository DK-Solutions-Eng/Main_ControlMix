#include "indicador_aeph.h"
#include "config_ControlMix.h"
#include "cartao_SD.h"
#include "relogio_DS1307.h"

uint8_t indicador;
char buffer[10] = {0};

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
	config_port();
	IHM_init();
	config_DS1307();
	config_SDCARD();
}

void loop()
{
	indicador=0x0A;
	
	while(1)
	{
		//RS232_TTL.println(get_peso(indicador));
		//RS232_TTL.println(get_tara(indicador));
		//remote_zero(indicador);
		
		get_peso(indicador).substring(0).toCharArray(buffer,10);
		
		//t13.setText(buffer);
		
		//led_peso_bruto();
		
		//digitalWrite(MAX485_CONTROLE_EX,HIGH);
		//RS485_externo.println("Teste");
		//digitalWrite(MAX485_CONTROLE_EX,LOW);
		
		//delay(100);
		
		//Serial.println("Funcionando!");
		
	}
}

void serialEvent2()
{
	while (RS485_externo.available())
	{
		char inChar = (char)RS485_externo.read();
		inputString += inChar;
		if (inChar == '\n')
		{
			stringComplete = true;
		}
	}
	
	if (stringComplete)
	{
		RS232_TTL.println(inputString);
		stringComplete = false;
		
		int cmd = inputString.substring(0, 2).toInt();

		switch (cmd)
		{
			case 60:
			atualiza_ds1307(inputString);
			break;
			
			default:
			break;
		}
	}
}

void led_peso_bruto()
{
	if(peso_bruto==1)
	{
		//p4.setPic(24);
		//p3.setPic(23);
	}
	if(peso_bruto==0)
	{
		//p4.setPic(23);
		//p3.setPic(24);
	}
}
