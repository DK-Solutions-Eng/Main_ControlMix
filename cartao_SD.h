/*
 * cartão_SD.h
 *
 * Created: 25/07/2018 21:02:31
 *  Author: Lucas Tadeu
 */ 

#ifndef CARTAO_SD_H_
#define CARTAO_SD_H_

#include <SPI.h>
#include <SD.h>

const int CS_pin = 53;
Sd2Card card;
SdVolume volume;
SdFile root;

void config_SDCARD();

void config_SDCARD()
{
	DEBUG.println(F("Inicializando SD Card..."));

	if (!card.init(SPI_HALF_SPEED, CS_pin))
	{
		DEBUG.println(F("Falha ao abrir cartão SD"));
		return;
	}
	else
	{
		DEBUG.println(F("Cartão SD iniciado com sucesso!"));
	}

	DEBUG.print("\nTipo do cartão: ");
	DEBUG.println(card.type());
	switch (card.type())
	{
		case SD_CARD_TYPE_SD1:
		Serial.println("SD1");
		break;
		case SD_CARD_TYPE_SD2:
		Serial.println("SD2");
		break;
		case SD_CARD_TYPE_SDHC:
		Serial.println("SDHC");
		break;
		default:
		Serial.println("Unknown");
	}

	if (!volume.init(card)) {
		Serial.println("Não foi possível encontrar a partição FAT16/FAT32.\nCertifique-se de ter formatado o cartão.");
		return;
	}

	// print the type and size of the first FAT-type volume
	uint32_t volumesize;
	Serial.print("\nTipo de volume é FAT");
	Serial.println(volume.fatType(), DEC);
	Serial.println();

	volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
	volumesize *= volume.clusterCount();       // we'll have a lot of clusters
	volumesize *= 512;                            // SD card blocks are always 512 bytes
	Serial.print("Volume size (bytes): ");
	Serial.println(volumesize);
	Serial.print("Volume size (Kbytes): ");
	volumesize /= 1024;
	Serial.println(volumesize);
	Serial.print("Volume size (Mbytes): ");
	volumesize /= 1024;
	Serial.println(volumesize);


	Serial.println("\nArquivos encontrados no cartão (nome, data e tamanho): ");
	root.openRoot(volume);

	// list all files in the card with date and size
	root.ls(LS_R | LS_DATE | LS_SIZE);
}


#endif /* CARTÃO_SD_H_ */