#include "config_ControlMix.h"
#include "indicador_aeph.h"
#include "cartao_SD.h"
#include "relogio_DS1307.h"
#include "IHM.h"

uint8_t indicador;
char buffer[10] = {0};

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
	config_port();
	//IHM_init();
	//config_DS1307();
	//config_SDCARD();
	
	pinMode(22,OUTPUT);
	digitalWrite(22,LOW);
	
	pinMode(40,OUTPUT);
}

void loop()
{
	indicador=0x0A;
	
	//digitalWrite(22,LOW);
	//delay(500);
	//digitalWrite(22,HIGH);
	//delay(500);
	
	//DEBUG.println(get_peso(0x0A));
	
	//buffer[0]=0x0A;
	//buffer[1]=0x03;
	//buffer[2]=0x00;
	//buffer[3]=0x0A;
	//buffer[4]=0x00;
	//buffer[5]=0x02;
	//buffer[6]=0x72;
	//buffer[7]=0xE5;
	
	//digitalWrite(40,HIGH);
	//Serial2.print(buffer);
	//digitalWrite(40,LOW);

	get_peso(indicador).substring(0).toCharArray(buffer,10);
	t13.setText(buffer);
	led_peso_bruto();
	
	nexLoop(nex_listen_list);
	
	//while(1)
	//{
		////RS232_TTL.println(get_peso(indicador));
		////RS232_TTL.println(get_tara(indicador));
		////remote_zero(indicador);
		//
		//get_peso(indicador).substring(0).toCharArray(buffer,10);
		//
		//DEBUG.println(buffer);
		//
		//t13.setText(buffer);
		//
		////led_peso_bruto();
		//
		////digitalWrite(MAX485_CONTROLE_EX,HIGH);
		////RS485_externo.println("Teste");
		////digitalWrite(MAX485_CONTROLE_EX,LOW);
		//
		////delay(100);
		//
		////Serial.println("Funcionando!");
		//
	//}
}

void led_peso_bruto()
{
	if(peso_bruto==1)
	{
		p4.setPic(24);
		p3.setPic(23);
	}
	if(peso_bruto==0)
	{
		p4.setPic(23);
		p3.setPic(24);
	}
}
