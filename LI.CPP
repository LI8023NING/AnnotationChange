#include<stdio.h>
/****************************************************
* 函数名  : main
* 功能描述: 取字符存字符
* 输入参数: 
* 输出参数:
* 返回值  : 无
* 作者    : 李宁 
* 创建日期: 2015/10/29 9:01:15
* 版权说明:
* 版权号  : V 1.2
****************************************************/

extern int CommentConvert(FILE *,FILE *);  //函数在别处定义

int main()
{
	FILE *Infp;
	FILE *Outfp;
	Infp = fopen("input.c","r"); //读文件
	if(NULL == Infp)
	{
		printf("Error:Open input.c file fail!\n");
		return -1;
	}
	Outfp = fopen("output.c","w"); //写文件
	if(NULL == Outfp)
	{
		printf("Error:Open output.c file fail!\n");
		return -1;
	}
	CommentConvert(Infp,Outfp);
	fclose(Infp);
	fclose(Outfp);
	return 0;
}