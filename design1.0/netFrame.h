#pragma once

#include "fsnMsg.h"
#include <QTNetwork/Qtnetwork>
//cmd
#define CMD_BILLINF 0x00
#define CMD_FPGA 0x01
#define CMD_FIX 0x02
#define CMD_IMG 0x06
#define CMD_WAVE 0x04
//#define CMD_IMG 0x06
#define CMD_CLOSENET 0xa0

//CMD_FIX
#define TYPE_FIX_START 0x01
#define TYPE_FIX_GETIMG 0x02
#define TYPE_FIX_APPLY 0x03
#define TYPE_FIX_LOCAL 0x04
#define TYPE_FIX_SAVE 0x05
#define TYPE_FIX_RESET 0x06

#pragma pack(push)  //Êý¾Ý¶ÔÆë 
#pragma pack(1)

class netFrame {
public:
	uint32_t start_word; //
	uint16_t fsn_count;
	uint32_t msg_length; //msg_length=42+fsn_count*100
	uint16_t cmd;
	uint8_t	 data[65535];   //2
	uint16_t check;
	uint32_t end_word;

	netFrame() {
		start_word = 0xaa55aa55;
		msg_length = 0;
		fsn_count = 0;
		cmd = 0;//no image ;if there is a image,cmd=0x30
		check = 0;
		end_word = 0x5555aaaa;
	}

	uint16_t getCheck()
	{
		u16 sum = 0;
		for (int i = 0; i<msg_length; i++)
		{
			sum += data[i];
		}
		return sum;
	}
	/*void send() {
	if (sc == 0)
	return;
	getCheck();
	write(sc, this, msg_length + 12);
	}*/
};

#pragma pack(pop)
