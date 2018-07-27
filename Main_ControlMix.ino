#include "config_ControlMix.h"
#include "indicador_aeph.h"
#include "cartao_SD.h"
#include "relogio_DS1307.h"
#include "IHM.h"

uint8_t indicador=0x0A;
char buffer[10] = {0};

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

unsigned long currentMillis;
unsigned long previousMillis = 0;

void setup()
{
	config_port();
	IHM_init();
	config_DS1307();
	config_SDCARD();
	
	pinMode(22,OUTPUT);
	digitalWrite(22,LOW);
}

void loop()
{
	currentMillis = millis();
	
	if (currentMillis - previousMillis >= 500)
	{
		previousMillis = currentMillis;
		digitalWrite(22,!digitalRead(22));
	}
	
	get_peso(indicador).substring(0).toCharArray(buffer,10);
	t13.setText(buffer);
	led_peso_bruto();
	
	nexLoop(nex_listen_list);
}
