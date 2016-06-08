/****************************************************
* ������  : ��ֹһ�����޴Ӳ�֤
* ��������: C++ע��ת��ΪC��ע��
* �������: C++ע��
* �������: Cע��
* ����ֵ  : Cע��
* ����    : ���� 
* ��������: 2015/10/29 8:29:39
* ��Ȩ˵��: �ڶ��棬δ�������Ͻ���������
* ��Ȩ��  : V 1.2
****************************************************/
#include<stdio.h>

#define UL unsigned long   //�����޷��ų����� UL

typedef enum               //��Ϊö�����ͣ��������״̬
{                          //�������ɳ��ֿո�
	NO_COMMENT_STATE,      //��״̬
	C_COMMENT_STATE,       //C״̬
	CPP_COMMENT_STATE,     //C++״̬
	END_STATE              //������־
}STATE_ENUM;               //�������

//����һ��״̬��
typedef struct STATE_MACHINE
{
	FILE *inputfile;    //�����ļ�ָ��
	FILE *outputfile;   //����ļ�ָ��
	STATE_ENUM ulstate; //����һ��ö�����͵ı��� ulstate
}STATE_MACHINE;         //Ϊ״̬��ȡ��Ϊ

/******************************************************************/
STATE_MACHINE g_state = {0};  //״̬���ṹ�����ͱ��������Ҷ����ʼ��Ϊ0
void EventPro(char ch);
void EventProAtNo(char ch);
void EventProAtC(char ch);
void EventProAtCpp(char ch);
/******************************************************************/
int CommentConvert(FILE *inputfile,FILE *outputfile)//(Infp,Outfp)
{
	if(inputfile == NULL || outputfile == NULL)//�ж��ļ��Ƿ�Ϊ��
	{
		printf("Error Open file fail!\n");
		return -1;
	}
//��ʼ��
	g_state.inputfile = inputfile;      //����
	g_state.outputfile = outputfile;    //���
	g_state.ulstate = NO_COMMENT_STATE; //״̬������״̬Ϊ��״̬
	
	char ch;
	while(g_state.ulstate != END_STATE)
	{
		ch = fgetc(g_state.inputfile);
		EventPro(ch);//�ж�ȡ���ĵ�һ���ַ�ch����ħ
	}
	return 0;
}

/****************************************************
* ������  : EventPro(char ch)
* ��������: 
* ����    : ���� 
* ��������: 2015/10/29 23:18:18
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
* ������  : 
* ��������:
* ����    : ���� 
* ��������: 2015/10/29 23:25:56
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
* ������  : 
* ��������:
* ����    : ���� 
* ��������: 2015/10/29 23:26:00
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
* ������  : 
* ��������:
* ����    : ���� 
* ��������: 2015/10/29 23:26:02
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