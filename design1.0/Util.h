#pragma once

#include<iostream>  
#include<cstdio> 
//#include <cstring>
#include <fstream>
#include <string>
using namespace std;

//输出数据到txt文件

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

//调试函数 输入字符串到txt
//输入


static int LogOutput(char *a, char* file, int line)
{
	FILE *fp;
	fp = fopen("log.txt", "at");
	fprintf(fp, a);
	fprintf(fp, "	in file: %s,	Line:%d\n", file, line);  //C和C++文件操作
	fclose(fp);
	//OutputDebugStringA(szLog);
	return 0;
}
