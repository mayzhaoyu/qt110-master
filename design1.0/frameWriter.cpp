#include "frameWriter.h"
#include "netFrame.h"


frameWriter::frameWriter()
{
}


frameWriter::~frameWriter()
{
}

void frameWriter::command(uint8_t function, uint8_t type) {
	frame.cmd = (uint16_t)function * 256;
	frame.cmd += type;
	frame.msg_length = (uint32_t)0;
	send();
}
void frameWriter::cmdFix(uint8_t type) {
	frame.cmd = CMD_FIX * 256;
	frame.cmd += type;
	//frame.data=...
	frame.msg_length = 0;//单单只frame.data的长度
	send();
}