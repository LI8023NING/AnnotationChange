#include<stdio.h>
/****************************************************
* ������  : main
* ��������: ȡ�ַ����ַ�
* �������: 
* �������:
* ����ֵ  : ��
* ����    : ���� 
* ��������: 2015/10/29 9:01:15
* ��Ȩ˵��:
* ��Ȩ��  : V 1.2
****************************************************/

extern int CommentConvert(FILE *,FILE *);

int main()
{
	FILE *Infp;
	FILE *Outfp;
	Infp = fopen("input.c","r");
	if(NULL == Infp)
	{
		printf("Error:Open input.c file fail!\n");
		return -1;
	}
	Outfp = fopen("output.c","w");
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