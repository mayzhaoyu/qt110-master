#pragma once

#include<iostream>  
#include<cstdio> 
//#include <cstring>
#include <fstream>
#include <string>
using namespace std;

//������ݵ�txt�ļ�

static int OutputDataToTxt(unsigned char*p, int size, char *s)
{
	int i;
	FILE *fp = fopen(s, "w");
	for (i = 0; i < size; i++)
	{

		fprintf(fp, "%x| ", p[i]);
	}
	fclose(fp);
	return 1;
}

//���Ժ��� �����ַ�����txt
//����


static int LogOutput(char *a, char* file, int line)
{
	FILE *fp;
	fp = fopen("log.txt", "at");
	fprintf(fp, a);
	fprintf(fp, "	in file: %s,	Line:%d\n", file, line);  //C��C++�ļ�����
	fclose(fp);
	//OutputDebugStringA(szLog);
	return 0;
}
