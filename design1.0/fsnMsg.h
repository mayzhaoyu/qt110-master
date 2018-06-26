#pragma once


#pragma pack(push)
#pragma pack(1)

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define u16 uint16_t

typedef struct {
	u16 HeadStart[4];
	u16 HeadString[6];
	uint32_t Counter;
	u16 HeadEnd[4];
}FSN_Header;



typedef struct {
	uint32_t Data[32];// 图像冠字号码点阵数据
}TImgSNoData;// 单个图像号码结构

typedef struct  {
	uint16_t Num; //字符数 2 字节
	uint16_t height, width; //每个图像字符高度和宽度 4 字节
	uint16_t Reserve2; //保留字 2 2 字节
	TImgSNoData SNo[12]; //128×12 字节
}TImageSNo;//图像冠字号码结构


typedef struct {
	u16 Date;
	u16 Time;
	u16 tfFlag;//真假币标志，0为假币或可疑币，1为真币，2为残币(清分机适用)，3为旧币(清分机适用)
	u16 ErrorCode[3];
	u16 MoneyFlag[4];
	u16 Ver;
	u16 Valuate;
	u16 CharNUM;
	u16 SN0[12];
	u16 MachineSNo[24];
	u16 Operate_No;
	TImageSNo ImageSNo;//若纸币信息中没有带图片信息，那么这个结构体将不被会发送
}FSN_Body;

typedef struct {
	u16 Date;
	u16 Time;
	u16 tfFlag;//真假币标志，0为假币或可疑币，1为真币，2为残币(清分机适用)，3为旧币(清分机适用)
	u16 ErrorCode[3];
	u16 MoneyFlag[4];
	u16 Ver;
	u16 Valuate;
	u16 CharNUM;
	u16 SN0[12];
	u16 MachineSNo[24];
	u16 Operate_No;
}FSN_Body_Small;


typedef struct {
	uint16_t derection;
	uint16_t length;
	uint16_t reserve;
}DebugMsg;

typedef struct {
	FSN_Header fsn_head;//32
	FSN_Body fsn_body;	//100+1544
	DebugMsg debugmsg;
	u16 checksum;		//2
	uint32_t end_word;	//4
}TCP_FSN_Msg;	//1682 

typedef struct {
	FSN_Header fsn_head;//32
	FSN_Body_Small fsn_body;	//100
	DebugMsg debugmsg;
	u16 checksum;		//2
	uint32_t end_word;	//4
}TCP_FSN_Msg_Sml;	//138


typedef struct MoneyResult
{
	char GZHresult[12];
	unsigned int isTrue;
	int money;
	int edition;
	int direction;
	int grayValue;				//灰度值0~255
	int length;					//send up 36 Bytes
	int width;
	int index;
	int reserved;
	int lineNum;				//白光图像行数
	int angle;
	unsigned char refuseFlag;	//据识标志，0正常，1据识，没有正确识别，过斜或其他原因
	unsigned char noteType;		//币种信息
	int pos[11];
}MoneyResult;

class billInf {
public:
	MoneyResult moneyResult;
	unsigned char GZHImage[3350];	//134*25 Gray Image
	billInf(int money=100) {
		moneyResult.direction = 1;
		moneyResult.edition = 2005;
		moneyResult.grayValue = 100;
		for (int i = 0; i < 10; i++) 
		{
			moneyResult.GZHresult[i] = '0' + i;
		}
		moneyResult.GZHresult[10] = 0;
		moneyResult.isTrue = 1;
		moneyResult.length = 65535;
		moneyResult.lineNum = 65535;
		moneyResult.money = money;
		moneyResult.width = 65535;
	}
};


#pragma pack(pop)