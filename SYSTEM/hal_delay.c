#include "hal_delay.h"


u16 fac_ms;//ȫ�ֱ���
u8 fac_us;//ȫ�ֱ���

/****************************************************
�������ܣ���ʱ��ʼ��   �鿴 ARM Corte-M3 (134ҳ) SysTick�Ĵ���
���������SYSCLK : ϵͳʱ��(72)MHZ
�����������
��    ע����
*****************************************************/
void Delay_Init(void)
{
	// SysTick_CLKSourceConfig();
	SysTick->CTRL &= ~BIT(2);		//ѡ���ⲿʱ��         ���ƺ�״̬�Ĵ���
	SysTick->CTRL &= ~BIT(1);		//�رն�ʱ������0����ж�����
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;	//Ϊϵͳʱ�ӵ�1/8  
	fac_ms=(int16_t)fac_us*1000;//ÿ��ms��Ҫ��systickʱ����   
}
/****************************************************
�������ܣ�ms����ʱ
���������nms : ����
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/				
void delay_ms(u16 nms)
{
	SysTick->LOAD = (u32) fac_ms * nms -1;//����ʱ��ֵ   ����ֵ�Ĵ���
	SysTick->VAL	= 1;//���д��ֵ��������ؼĴ�����ֵ     ��ǰֵ�Ĵ���  
	SysTick->CTRL |= BIT(0);	//SysTick ʹ��
	while(!(SysTick->CTRL &(1<<16)));	//�ж��Ƿ����0     ���ƺ�״̬�Ĵ���
	SysTick->CTRL &= ~BIT(0);		//�ر�SysTick
}
/****************************************************
�������ܣ�us����ʱ
���������nus : ΢��
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/	
void delay_us(u32 nus)
{
	SysTick->LOAD = (u32) fac_us * nus -1;	//����ʱ��ֵ
	SysTick->VAL  = 1;	//���д��ֵ��������ؼĴ�����ֵ
	SysTick->CTRL |= BIT(0);		//SysTick ʹ��
	while(!(SysTick->CTRL &(1<<16)));	//�ж��Ƿ����0
	SysTick->CTRL &= ~BIT(0);	//�ر�SysTikc;
}












