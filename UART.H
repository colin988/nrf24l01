/******************************************************************************/
/*                        -- ���ڰ��ſɿƼ����޹�˾ --                        */
/*
//  �ļ�����uart.h                                                              
//  ˵�������ں궨��                                                                  
//  ��д��Ա��Wu                                                                   
//  ��д���ڣ�2012��11��12��                                                              
//  ����ά����
//	ά����¼��
//
//                                                          
*/ 
// �����������ó��������ѧϰ�뽻�� 
// (c) Anxinke Corporation. All rights reserved.                                                               
/******************************************************************************/
#ifndef __UART_H
#define __UART_H

#define UART_BUAD                            115200



void uartInit(void);
void uartSendData(u8 ucData);
void uartSendString(char *s);




#endif