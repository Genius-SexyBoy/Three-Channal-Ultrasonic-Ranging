

#include <STC15F2K60S2.H>
#include "Mid_oled.h"
#include <stdio.h>
#include "delay.h"

//#include "bmp.h"

sbit Tx  = P3^2;     //�����������ţ���ʱ 20us
sbit Rx  = P3^3;    //�ز����ţ������ⲿ�ж� 1����Щ���ſ�����ı䡣

sbit Tx1 = P1^3;
sbit Rx1 = P1^2;

sbit Tx2 = P1^5;
sbit Rx2 = P1^4;

sbit LED = P5^5;
bit TimeUp = 0;   //��ʱ�������־λ
long xdata Th0,Tl0,Th1,Tl1,Th2,Tl2;
unsigned long time0 = 0;
unsigned int Measureresult = 0;


void GPIO_Init(void)
{
	P1M0 = 0;  P1M1 = 0;
	P2M0 = 0;  P2M1 = 0;
	P3M0 = 0;  P3M1 = 0;
	P5M0 = 0;  P5M1 = 0;
}


unsigned int Measure(void)
{
	char Del20us = 0;                 //��ʱ�������ڳ��������������в��� 20us �ķ���
	char RxBack = 1;                 //���������ر�־λ
	TMOD = 0x01;                    //��ʱ��������ʽ 1��16 λ����ֵ������װ
	Tx = 0;                        //���������������ŵ�λ����
	Th0 = 0;                      //��ʼ������ֵ
	Tl0 = 0;                     //��ʼ������ֵ
	TimeUp = 0;                 //��ʼ��
	EA = 1;
	ET0 = 1;                  //����ʱ�� 0 �ж�TR0=0;//�ض�ʱ�� 0
	TH0 = 0;                 //����ʱ����ʼֵ�� 8 λΪ 0
	TL0 = 0;                //����ʱ����ʼֵ�� 8 λΪ 0
	Tx = 1;                //���߳������������ŵ�λ
	for(Del20us = 20;Del20us > 0;Del20us--);//��ʱ 20us
	Tx = 0;              //���ͳ������������ŵ�λ��ʹ֮���� 20us �ķ����źţ�ʹ������ģ�鿪ʼ������
	while(Rx == 0);     //�ȴ��ز����ű� 1��
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;          //����ʱ�� 0
	               //ʹ�������ѯ�ķ�ʽ����ⳬ�����ز����ţ��ж��Ƿ����������أ�����ʹ���ⲿ�жϵ�
	              //��ʽ��������չ���������ģ�顣
	while(RxBack)
	{
		if(Rx == 0 || TimeUp == 1)
			{
				TR0 = 0;
				Th0 = TH0;
				Tl0 = TL0;
				TR0 = 1;
				RxBack = 0;
			}
	}
	while(!TimeUp);                                         //�ȴ���ʱ�����
	time0 = (Th0 * 256 + Tl0);                             //ȡ����ʱ����ֵ
	Measureresult = ((unsigned long)(344) * time0) / 2000;//�����Ľ����λΪ mm
	if(Measureresult < 30 || Measureresult > 900)
		{
			Measureresult = 0;
		}	                        //���˵�һЩ�쳣�����ݣ����������ľ��벻�� 30��900mm ʱ����ֵΪ 0
	return Measureresult;
}


unsigned int Measure_Sec(void)
{
	char Del20us = 0;                 //��ʱ�������ڳ��������������в��� 20us �ķ���
	char RxBack = 1;                 //���������ر�־λ
	TMOD = 0x01;                    //��ʱ��������ʽ 1��16 λ����ֵ������װ
	Tx1 = 0;                        //���������������ŵ�λ����
	Th1 = 0;                      //��ʼ������ֵ
	Tl1 = 0;                     //��ʼ������ֵ
	TimeUp = 0;                 //��ʼ��
	EA = 1;
	ET0 = 1;                  //����ʱ�� 0 �ж�TR0=0;//�ض�ʱ�� 0
	TH0 = 0;                 //����ʱ����ʼֵ�� 8 λΪ 0
	TL0 = 0;                //����ʱ����ʼֵ�� 8 λΪ 0
	Tx1 = 1;                //���߳������������ŵ�λ
	for(Del20us=20;Del20us>0;Del20us--);//��ʱ 20us
	Tx1 = 0;              //���ͳ������������ŵ�λ��ʹ֮���� 20us �ķ����źţ�ʹ������ģ�鿪ʼ������
	while(Rx1 == 0);     //�ȴ��ز����ű� 1��
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;          //����ʱ�� 0
	                 //ʹ�������ѯ�ķ�ʽ����ⳬ�����ز����ţ��ж��Ƿ����������أ�����ʹ���ⲿ�жϵ�
	                //��ʽ��������չ���������ģ�顣
	while(RxBack)
	{
		if(Rx1 == 0 || TimeUp == 1)
			{
				TR0 = 0;
				Th1 = TH0;
				Tl1 = TL0;
				TR0 = 1;
				RxBack = 0;
			}
	}
	while(!TimeUp);                                   //�ȴ���ʱ�����
	time0 = (Th1*256 + Tl1);                             //ȡ����ʱ����ֵ
	Measureresult = ((unsigned long)(344) * time0) / 2000;//�����Ľ����λΪ mm
	if(Measureresult < 30 || Measureresult > 900)
		{
			Measureresult = 0;
		}	                        //���˵�һЩ�쳣�����ݣ����������ľ��벻�� 30��900mm ʱ����ֵΪ 0
	return Measureresult;
}



unsigned int Measure_Thr(void)
{
	char Del20us = 0;                 //��ʱ�������ڳ��������������в��� 20us �ķ���
	char RxBack = 1;                 //���������ر�־λ
	TMOD = 0x01;                    //��ʱ��������ʽ 1��16 λ����ֵ������װ
	Tx2 = 0;                        //���������������ŵ�λ����
	Th2 = 0;                      //��ʼ������ֵ
	Tl2 = 0;                     //��ʼ������ֵ
	TimeUp = 0;                 //��ʼ��
	EA = 1;
	ET0 = 1;                  //����ʱ�� 0 �ж�TR0=0;//�ض�ʱ�� 0
	TH0 = 0;                 //����ʱ����ʼֵ�� 8 λΪ 0
	TL0 = 0;                //����ʱ����ʼֵ�� 8 λΪ 0
	Tx2 = 1;                //���߳������������ŵ�λ
	for(Del20us=20;Del20us>0;Del20us--);//��ʱ 20us
	Tx2 = 0;              //���ͳ������������ŵ�λ��ʹ֮���� 20us �ķ����źţ�ʹ������ģ�鿪ʼ������
	while(Rx2 == 0);     //�ȴ��ز����ű� 1��
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;          //����ʱ�� 0
	               //ʹ�������ѯ�ķ�ʽ����ⳬ�����ز����ţ��ж��Ƿ����������أ�����ʹ���ⲿ�жϵ�
	              //��ʽ��������չ���������ģ�顣
	while(RxBack)
	{
		if(Rx2 == 0 || TimeUp == 1)
			{
				TR0 = 0;
				Th2 = TH0;
				Tl2 = TL0;
				TR0 = 1;
				RxBack = 0;
			}
	}
	while(!TimeUp);                                   //�ȴ���ʱ�����
	time0 = (Th2 * 256 + Tl2);                             //ȡ����ʱ����ֵ
	Measureresult = ((unsigned long)(344) * time0) / 2000;//�����Ľ����λΪ mm
	if(Measureresult < 30 || Measureresult > 900)
		{
			Measureresult = 0;
		}	                        //���˵�һЩ�쳣�����ݣ����������ľ��벻�� 30��900mm ʱ����ֵΪ 0
	return Measureresult;
}



void T0_time() interrupt 1
{
	TimeUp = 1;
}

void main(void)
{
	unsigned int ge,shi,bai;
	unsigned char flag;
	unsigned int j = 0;
	GPIO_Init();
	Mid_oled_Display_Control(DisInit);
	Mid_oled_Display_Control(Char_Size_16);
	LED = 1;
	while(1)
	{
		ge   = Measure()%100%10;
		shi  = Measure()%100/10;
		bai  = Measure()/100;
		ShowData(2,0,bai);
		ShowData(2,10,shi);
		ShowData(2,20,ge);
		ge  = Measure_Sec()%100%10;
		shi = Measure_Sec()%100/10;
		bai = Measure_Sec()/100;
		ShowData(4,0,bai);
		ShowData(4,10,shi);
		ShowData(4,20,ge);
		ge  = Measure_Thr()%100%10;
		shi = Measure_Thr()%100/10;
		bai = Measure_Thr()/100;
		ShowData(6,0,bai);
		ShowData(6,10,shi);
		ShowData(6,20,ge);
		flag = 0;	
		Mid_oled_Display_Show(30,2,ShowString,"mm",NULL);		
		Mid_oled_Display_Show(30,4,ShowString,"mm",NULL);	
		Mid_oled_Display_Show(30,6,ShowString,"mm",NULL);
		LED = 0;
		delayms(50);
		LED = 1;
		delayms(50);
	}
}
