/**
  ******************************************************************************
  * @file    bsp_usart3.c
  * @author  xiaoyuan
  * @version V1.0
  * @date    2018-11-06
  * @brief   config usart3
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "bsp_usart3.h"
#include <stdarg.h>
#include <string.h> 
#include <stdio.h>


RxFramTypeDef rxFram = {0};

/**
  * @brief  ��ʼ������3
  * @param  bound�����ڲ����ʣ�һ������Ϊ115200
  * @retval None
  */
void usart3_init(uint32_t bound) 
{
  /*�����ʼ���ṹ��*/
  GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/* ����GPIOB�˿�ʱ�Ӽ�USART3����ʱ�� */
  RCC_APB1PeriphClockCmd(USART3_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(USART3_GPIO_CLK, ENABLE); 
 	
	/* ��λ����1 */
	USART_DeInit(USART3);  //��λ����1
	
	/* ����USART3_TX��PB10������GPIO״̬ */
  GPIO_InitStructure.GPIO_Pin = USART3_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(USART3_TX_PORT, &GPIO_InitStructure);   

  /* ����USART3_RX��PB11������GPIO״̬ */
  GPIO_InitStructure.GPIO_Pin = USART3_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(USART3_RX_PORT, &GPIO_InitStructure);  

  /* USART ��ʼ������ */
	USART_InitStructure.USART_BaudRate = bound;  //�����ʣ�һ������Ϊ115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //�ֳ���Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //ֹͣλ��һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;  //У��λ������żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������:��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//����ģʽ���շ�ģʽ
  USART_Init(USART3, &USART_InitStructure);  //����ָ���Ĳ�����ʼ������1
  
  /* ����Ƕ�������жϿ�����NVIC */ 
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;  //����USART1Ϊ�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	 //����ָ���Ĳ�����ʼ��NVIC�Ĵ���
	
  /* ʹ�ܴ��ڽ����ж� */ 
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  /* ����3ʹ�� */
  USART_Cmd(USART3, ENABLE);
}

void usart3_sendByte(uint8_t c)
{
  USART_SendData(USART3, c);
  while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

void usart3_sendStr(char * str)
{
  while(*str != '\0')
  {
    usart3_sendByte(*str++);
  }
}

//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_BUFFER_LEN�ֽ�
void usart3_printf(char* fmt,...)  
{
  char buffer[USART3_BUFFER_LEN+1];  
	uint16_t i,j; 

	va_list ap; 
	va_start(ap, fmt);
	vsprintf((char*)buffer, fmt, ap);
	va_end(ap);
	i = strlen((const char*)buffer);		//�˴η������ݵĳ���
	for(j = 0; j < i; j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,buffer[j]); 
	} 
}

uint8_t dataStartFlag = 0;

/**
  * @brief  USART3�����жϷ�����
  * @param  none
  * @retval none
  */ 
void USART3_IRQHandler(void) 
{
	uint8_t rec;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
	{
		rec = USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������
    //if(rec == ':')
    //{
      //dataStartFlag = 1;
      //rec = USART_ReceiveData(USART3);
    //}
    //if(dataStartFlag == 1)
    //{
    if(rxFram.length < USART3_RX_MAX_LEN - 1) //Ԥ��һ���ֽ�д������
      rxFram.rxbuffer[rxFram.length++] = rec;
    //}
  } 
  if(USART_GetITStatus(USART3, USART_IT_IDLE) == SET)    //����֡�������
	{
    rxFram.finishFlag = 1; //������ɱ�־λ��λ
    //dataStartFlag = 0;
		
		rec = USART_ReceiveData(USART3);  //�������������жϱ�־λ(�ȶ�USART_SR��Ȼ���USART_DR)	
  }
} 


