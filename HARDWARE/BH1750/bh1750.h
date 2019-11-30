#ifndef __BH1750_H__
#define __BH1750_H__

#define BH1750_Addr 0x46
#define BH1750_ON   0x01
#define BH1750_CON  0x10
#define BH1750_ONE  0x20
#define BH1750_RSET 0x07

void Init_BH1750(void);								  //IO��ʼ����
void Start_BH1750(void);			//�ϵ磬����������ݼĴ���
void Read_BH1750(void);                               //�����Ķ�ȡ�ڲ��Ĵ�������
void Convert_BH1750(void);
#endif

