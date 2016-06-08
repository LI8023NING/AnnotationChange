/****************************************************
* 函数名  : 不止一个，无从查证
* 功能描述: C++注释转换为C的注释
* 输入参数: C++注释
* 输出参数: C注释
* 返回值  : C注释
* 作者    : 李宁 
* 创建日期: 2015/10/29 8:29:39
* 版权说明: 第二版，未经允许，严禁大量盗版
* 版权号  : V 1.2
****************************************************/
#include<stdio.h>

#define UL unsigned long   //定义无符号长整型 UL

typedef enum               //此为枚举类型，定义各类状态
{                          //命名不可出现空格
	NO_COMMENT_STATE,      //无状态
	C_COMMENT_STATE,       //C状态
	CPP_COMMENT_STATE,     //C++状态
	END_STATE              //结束标志
}STATE_ENUM;               //起个名字

//定义一个状态机
typedef struct STATE_MACHINE
{
	FILE *inputfile;    //输入文件指针
	FILE *outputfile;   //输出文件指针
	STATE_ENUM ulstate; //定义一个枚举类型的变量 ulstate
}STATE_MACHINE;         //为状态机取名为

/******************************************************************/
STATE_MACHINE g_state = {0};  //状态机结构体类型变量，并且对其初始化为0
void EventPro(char ch);
void EventProAtNo(char ch);
void EventProAtC(char ch);
void EventProAtCpp(char ch);
/******************************************************************/
int CommentConvert(FILE *inputfile,FILE *outputfile)//(Infp,Outfp)
{
	if(inputfile == NULL || outputfile == NULL)//判断文件是否为空
	{
		printf("Error Open file fail!\n");
		return -1;
	}
//初始化
	g_state.inputfile = inputfile;      //输入
	g_state.outputfile = outputfile;    //输出
	g_state.ulstate = NO_COMMENT_STATE; //状态机定义状态为无状态
	
	char ch;
	while(g_state.ulstate != END_STATE)
	{
		ch = fgetc(g_state.inputfile);
		EventPro(ch);//判断取出的第一个字符ch是神魔
	}
	return 0;
}

/****************************************************
* 函数名  : EventPro(char ch)
* 功能描述: 
* 作者    : 李宁 
* 创建日期: 2015/10/29 23:18:18
****************************************************/
void EventPro(char ch)
{
	switch(g_state.ulstate)
	{
	case NO_COMMENT_STATE:
			EventProAtNo(ch);
			break;
	case C_COMMENT_STATE:
			EventProAtC(ch);
			break;
	case CPP_COMMENT_STATE:
			EventProAtCpp(ch);
			break;
	case END_STATE:
			break;
	default:
			break;
	}
}

/****************************************************
* 函数名  : 
* 功能描述:
* 作者    : 李宁 
* 创建日期: 2015/10/29 23:25:56
****************************************************/
void EventProAtNo(char ch)
{
	char nextch;
	switch(ch)
	{
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
			fputc(ch,g_state.outputfile);
			fputc('*',g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;
		}
		else if(nextch = '*')
		{
			fputc(ch,g_state.outputfile);
			fputc('*',g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		else
		{

		}
		break;
	case '\n':
		fputc('\n',g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	/*case '"':
		fputc(ch,g_state.outputfile);
		g_state.ulstate = C_COMMENT_STATE;
		break;*/
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
/****************************************************
* 函数名  : 
* 功能描述:
* 作者    : 李宁 
* 创建日期: 2015/10/29 23:26:00
****************************************************/
void EventProAtC(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		}
		else
		{
	
		}
		break;
	case '/':
		fputc(' ',g_state.outputfile);
		g_state.ulstate = C_COMMENT_STATE;
		break;
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
/****************************************************
* 函数名  : 
* 功能描述:
* 作者    : 李宁 
* 创建日期: 2015/10/29 23:26:02
****************************************************/
void EventProAtCpp(char ch)
{
	switch(ch)
	{
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	case '\n':
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		fputc('\n',g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	case '*':
		fputc(' ',g_state.outputfile);
		break;
	case '/':
		fputc(' ',g_state.outputfile);
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}