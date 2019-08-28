/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 ����0 ��ѯ�շ���ʾ,ʵ�����ݻػ�
                      ע�����DEBUG.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\UART\UART.H"
#pragma  NOAREGS

/********************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void main( void )
{
    UINT8 dat;
	
    CfgFsys( );                                                                	/* CH543ʱ��ѡ������ */
    mDelaymS( 20 );																/* ����ʱ�Ӻ�,������ʱ�ȶ�ʱ�� */
    mInitSTDIO( );                                                             	/* ����0��ʼ�� */
	printf("UART demo start ...\n");
    
	while( 1 )
    {
        dat = CH543UART0RcvByte( );
        CH543UART0SendByte( dat );
    }
}