/********************************** (C) COPYRIGHT *******************************
* File Name          : UART.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 ���ڳ�ʼ�����
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


#ifndef __UART_H__
#define __UART_H__

/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"

/*******************************************************************************/
/* �������� */
extern UINT8 CH543UART0RcvByte( void );                 					 	/* UART0����һ���ֽ� */
extern void  CH543UART0SendByte( UINT8 SendDat );     							/* UART0����һ���ֽ� */

#endif