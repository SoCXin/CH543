/********************************** (C) COPYRIGHT *******************************
* File Name          : UART.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 ���ڳ�ʼ�����
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\UART\UART.H"
#pragma  NOAREGS

/********************************************************************************
* Function Name  : CH543UART0RcvByte( void )
* Description    : CH543UART0����һ���ֽ�
* Input          : None
* Output         : None
* Return         : SBUF
********************************************************************************/
UINT8 CH543UART0RcvByte( void )
{
    while( RI == 0 );    														/* ��ѯ���� */
	RI = 0;                                   	                      			/* ��������жϱ�־λ */
    return SBUF;
}

/********************************************************************************
* Function Name  : CH543UART0SendByte( UINT8 SendDat )
* Description    : CH543UART0����һ���ֽ�
* Input          : SendDat -> Ҫ���͵�����
* Output         : None
* Return         : None
********************************************************************************/
void CH543UART0SendByte( UINT8 SendDat )
{
	TI = 0;
    SBUF = SendDat;
    while( TI == 0 );															/* ��ѯ�ȴ�������� */
    TI = 0;                                                          			/* �����������ж� */
}