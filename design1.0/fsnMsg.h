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
	uint32_t Data[32];// ͼ����ֺ����������
}TImgSNoData;// ����ͼ�����ṹ

typedef struct  {
	uint16_t Num; //�ַ��� 2 �ֽ�
	uint16_t height, width; //ÿ��ͼ���ַ��߶ȺͿ�� 4 �ֽ�
	uint16_t Reserve2; //������ 2 2 �ֽ�
	TImgSNoData SNo[12]; //128��12 �ֽ�
}TImageSNo;//ͼ����ֺ���ṹ


typedef struct {
	u16 Date;
	u16 Time;
	u16 tfFlag;//��ٱұ�־��0Ϊ�ٱһ���ɱң�1Ϊ��ң�2Ϊ�б�(��ֻ�����)��3Ϊ�ɱ�(��ֻ�����)
	u16 ErrorCode[3];
	u16 MoneyFlag[4];
	u16 Ver;
	u16 Valuate;
	u16 CharNUM;
	u16 SN0[12];
	u16 MachineSNo[24];
	u16 Operate_No;
	TImageSNo ImageSNo;//��ֽ����Ϣ��û�д�ͼƬ��Ϣ����ô����ṹ�彫�����ᷢ��
}FSN_Body;

typedef struct {
	u16 Date;
	u16 Time;
	u16 tfFlag;//��ٱұ�־��0Ϊ�ٱһ���ɱң�1Ϊ��ң�2Ϊ�б�(��ֻ�����)��3Ϊ�ɱ�(��ֻ�����)
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
	int grayValue;				//�Ҷ�ֵ0~255
	int length;					//send up 36 Bytes
	int width;
	int index;
	int reserved;
	int lineNum;				//�׹�ͼ������
	int angle;
	unsigned char refuseFlag;	//��ʶ��־��0������1��ʶ��û����ȷʶ�𣬹�б������ԭ��
	unsigned char noteType;		//������Ϣ
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