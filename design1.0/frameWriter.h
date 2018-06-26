#pragma once
#include "fsnMsg.h"
#include "netFrame.h"
#include <QTNetwork/Qtnetwork>

class frameWriter
{
	//Q_OBJECT
public:
	netFrame frame;
	QTcpSocket **psocket;
	frameWriter(QTcpSocket ** psocket) {
		frame.start_word = 0xaa55aa55;
		frame.msg_length = 0;
		frame.fsn_count = (uint16_t)1;
		frame.cmd = 0x31;//no image ;if there is a image,cmd=0x30
		frame.end_word = 0x5555aaaa;
		this->psocket = psocket;
	}
	uint16_t getCheck() {
		u16 sum = 0;
		for (int i = 0; i<frame.msg_length; i++) {
			sum += frame.data[i];
		}
		frame.check = sum;
		return sum;
	}
	void fixend() {
		*(uint16_t*)(frame.data + frame.msg_length) = frame.check;
		*(uint32_t*)(frame.data + frame.msg_length + 2) = frame.end_word;
	}
	void send() {
		if (*psocket == 0)
			return;
		getCheck();
		fixend();//把帧尾值与校验码复制到数据结尾
				 //write(sc, &frame, frame.msg_length + 12 + 6);
		int a = sizeof(frame.fsn_count);
		(*psocket)->write((const char*)(&frame), frame.msg_length + 12 + 6 );  
		
		//char p[]=
	}
	frameWriter();
	~frameWriter();
public slots:
	void command(uint8_t function, uint8_t type);
	void cmdFix(uint8_t type);
};

