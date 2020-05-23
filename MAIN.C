/******************************************************************************/
/*                        -- ���ڰ��ſɿƼ����޹�˾ --                        */
/*
//  �ļ�����main.c                                                              
//  ˵�������ͻ�����ģ��ͨ��ʹ�ó���                                                                  
//  ��д��Ա��                                                                   
//  ��д���ڣ�                                                              
//  ����ά����
//  ά����¼��
//
//                                                          
*/ 
// �����������ó��������ѧϰ�뽻�� 
// (c) Anxinke Corporation. All rights reserved.                                                               
/******************************************************************************/
#include "typedef.h"
#include "gpio.h"
#include "uart.h"
#include "nrf_24l01.h"
#include "delay.h"

/******************************************************************************/
// �������ƣ�main 
// ��������� 
// ��������� 
// �������ܣ� 
/******************************************************************************/
void main(void)
{
  unsigned char i=0;

  unsigned int count_send=0;
  unsigned int rec_new=0;
  unsigned int rec_old=0;
  unsigned int rec_err=0;
  unsigned int lock_key=0;
  uartInit();

  Delay100ms();
  init_nrf24l01_io();
  led=0;
  Delay100ms();
  led=1;
  Delay100ms();
  led=0;
  Delay100ms();
  led=1;
  Delay100ms();
  TI=1;
  Delay100ms();
  uartSendString("READY!\r\n");
  ifnnrf_rx_mode();

  while(1)
  {

    KEY=1;
    KEY2 = 1;
    while(KEY == 0 || KEY2 == 0){
        IRQ=1;
        SPI_RW_Reg(WRITE_REG+STATUS,0xff);
        if (KEY == 0) {
            tx_buf[0]=0xAA;
        } else if (KEY2 == 0) {
            tx_buf[0]=0x55;
        }
        ifnnrf_tx_mode();
        while(IRQ);
        sta=SPI_Read(STATUS);
        SPI_RW_Reg(WRITE_REG+STATUS,0xff);
        if(sta&STA_MARK_TX){
            if (KEY == 0){
        		led=0;
        		Delay100ms();
        		led=1;
                Delay100ms();
            } else {
        		led2=0;
        		Delay100ms();
        		led2=1;
                Delay100ms();
            }
	   } else {
            ifnnrf_CLERN_ALL();
	   }
	   lock_key=1;

    }	//����
    if(lock_key) {
        lock_key=0;
        ifnnrf_rx_mode();
        IRQ=1;
        while(IRQ==0);
        _delay_us(400);
    }
    IRQ=1;
    if(IRQ==0) {        
        sta=SPI_Read(STATUS);
        SPI_RW_Reg(WRITE_REG+STATUS,0xff);
        
        if(sta&STA_MARK_RX) { 
            SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);
            if (rx_buf[0] == 0xAA) {
                uartSendString("�㰴������߰���\r\n");
                led=0;
                Delay100ms();
                led=1;
                Delay100ms();
            } else if (rx_buf[0] == 0x55)  {
                uartSendString("�㰴�����ұ߰���\r\n");
        		led2=0;
        		Delay100ms();
        		led2=1;
                Delay100ms();
            }
            rx_buf[0] = 0;
        } else {
            ifnnrf_CLERN_ALL();
            ifnnrf_rx_mode();
            IRQ=1;
            while(IRQ==0);
        }
    } //����
	  
  }
}