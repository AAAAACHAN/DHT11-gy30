#include "BH1750.h"
#include "i2c.h"
#include "delay.h"

float result_lx=0;
u8 BUF[2]={0};
u16 result=0;

//��ʼ��
void Init_BH1750(void)
{
	i2c_Port_Init();
}

void Cmd_Write_BH1750(u8 cmd)
{
    I2C_Start();                  //��ʼ�ź�
    I2C_Send_Byte(BH1750_Addr+0);   //�����豸��ַ+д�ź�
	while(I2C_Wait_Ack());
    I2C_Send_Byte(cmd);    //�ڲ��Ĵ�����ַ
	while(I2C_Wait_Ack());
    //BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                   //����ֹͣ�ź�
	delay_ms(5);
}
void Start_BH1750(void)
{
	Cmd_Write_BH1750(BH1750_ON);	 //power on
	Cmd_Write_BH1750(BH1750_RSET);	//clear
	Cmd_Write_BH1750(BH1750_ONE);  //һ��H�ֱ���ģʽ������120ms��֮���Զ��ϵ�ģʽ  
}
void Read_BH1750(void)
{   	
    I2C_Start();                          //��ʼ�ź�
    I2C_Send_Byte(BH1750_Addr+1);         //�����豸��ַ+���ź�
	while(I2C_Wait_Ack());
	BUF[0]=I2C_Read_Byte(1);  //����ACK
	BUF[1]=I2C_Read_Byte(0);  //����NACK

    I2C_Stop();                          //ֹͣ�ź�
    delay_ms(5);
}

void Convert_BH1750(void)
{
	result=BUF[0];
	result=(result<<8)+BUF[1];  //�ϳ����ݣ�����������
	result_lx=(float)result/1.2;

}


