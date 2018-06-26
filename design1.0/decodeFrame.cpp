#include "decodeFrame.h"

void decodeFrame::caseHead(unsigned char ch) {
	switch (index)
	{
		//
	case 0:
		if (ch != 0x55) {
			index = 0;
			return;
		}
		break;
	case 1:
		if (ch != 0xaa) {
			index = 0;
			return;
		}
		break;
	case 2:
		if (ch != 0x55) {
			index = 0;
			return;
		}
		break;
	case 3:
		if (ch != 0xaa) {
			index = 0;
			return;
		}
		flag = 1;
		break;
	default:
		return;
	}
	index++;
}

void decodeFrame::caseGetLength(unsigned char ch) {
	switch (index)
	{
		//ͷ
	case 4:
		frame.fsn_count = ch;
		break;
	case 5:
		frame.fsn_count += ((uint32_t)ch<<8);
		break;
	case 6:
		frame.msg_length = ch;
		break;
	case 7:
		frame.msg_length += ((uint32_t)ch<<8);
		break;
	case 8:
		frame.msg_length += ((uint32_t)ch << 16);
		break;
	case 9:
		frame.msg_length += ((uint32_t)ch << 24);
		break;
	case 10:
		frame.cmd = ch;
		break;
	case 11:
		frame.cmd += ((uint16_t)ch) << 8;
		flag = 2;
		restNum = frame.msg_length + 6;
		break;
	default:
		qDebug("default");
		return;
	}
	
	qDebug("%d \n", index);
	index = index + 1;
}

bool decodeFrame::checkEnd() {
	if (frame.end_word != 0x5555aaaa) {
		index = 0;
		flag = 0;
		return false;
	}
	else {
		flag = 3;
		return true;
	}
}



/*****************************************/


