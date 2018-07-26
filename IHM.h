/*
 * IHM.h
 *
 * Created: 25/06/2018 11:18:34
 *  Author: Lucas Tadeu
 */ 

#include "Nextion.h"

#ifndef IHM_H_
#define IHM_H_

char temp_un[2] = {0};
	
void IHM_init();
void t13PopCallback(void *ptr);

/*
* Declare a text object [page id:0,component id:13, component name: "t13"].
*/
NexText t13 = NexText(0, 13, "t13");
NexPicture p3 = NexPicture(0, 30, "p3");
NexPicture p4 = NexPicture(0, 33, "p4");

NexTouch *nex_listen_list[] =
{
	&t13,
	&p3,
	&p4,
	NULL
};

void t13PopCallback(void *ptr)
{
	dbSerialPrintln("t13PopCallback");
}

void p3PopCallback(void *ptr)
{
	uint32_t number = 0;
	dbSerialPrintln("p3PopCallback");

	p3.getPic(&number);

	if (number == 23)
	{
		number = 24;
	}
	else
	{
		number = 23;
	}
	
	p3.setPic(number);
}
void p4PopCallback(void *ptr)
{
	uint32_t number = 0;
	dbSerialPrintln("p4PopCallback");

	p4.getPic(&number);

	if (number == 23)
	{
		number = 24;
	}
	else
	{
		number = 23;
	}
	
	p4.setPic(number);
}

void IHM_init(void)
{
	nexInit();
	t13.attachPop(t13PopCallback);
	p3.attachPop(p3PopCallback);
	p4.attachPop(p4PopCallback);
}



#endif /* IHM_H_ */