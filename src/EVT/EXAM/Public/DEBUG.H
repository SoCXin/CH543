/********************************** (C) COPYRIGHT *******************************
* File Name          : DEBUG.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/1/5
* Description        : CH5XX DEBUG Interface
                     (1)����Ƶ����;
                     (2)��us\ms������ʱ����;										 
                     (3)������0�����ӡ��Ϣ,�����ʿɵ�;            				   
                     (4)�����Ź���ʼ���͸�ֵ����;    										 
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



#ifndef	__DEBUG_H__
#define __DEBUG_H__

/*******************************************************************************/
/* ͷ�ļ����� */
#include <absacc.h>
#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include ".\Public\CH543.H"

/*******************************************************************************/
/* ��غ궨�� */

/* ��������ֵ */
#ifndef  SUCCESS
#define  SUCCESS		1
#endif
#ifndef  FAIL
#define  FAIL			0
#endif

/* ��ʱ����ʼ */
#ifndef  START
#define  START			1
#endif
#ifndef  STOP
#define  STOP			0
#endif

/* ���Կ��� */
#ifndef  DE_PRINTF                       
#define  DE_PRINTF		1
#endif

/* ϵͳ��Ƶ48MHz */
#define	 FREQ_SYS		48000000

/* PD������Ƶ48MHz */
#ifndef  UPD_TMR_RX
#define	UPD_TMR_RX = UPD_TMR_RX_48M;
#define	UPD_TMR_TX = UPD_TMR_TX_48M;
#endif

/* ���ٻ��� */
#define	 WAKEUP_FAST	0				         

/* ������ */
#ifndef  UART0BUAD
#define  UART0BUAD     	115200
#endif

/* ����Сֵ */
#ifndef MIN
#define MIN( a, b )		( ( ( a ) <= ( b ) ) ? ( a ) : ( b ) )
#endif

/*******************************************************************************/
/* �������� */
extern void CfgFsys( void );                        							/* CH543ʱ��ѡ������� */
extern void mDelayuS( UINT16 n );              									/* ��uSΪ��λ��ʱ */
extern void	mDelaymS( UINT16 n );              									/* ��mSΪ��λ��ʱ */
extern void CH543UART0Alter( void );                 							/* CH543����0����ӳ�䵽P3.0/P3.1 */
extern void	mInitSTDIO( void );                     							/* T1��Ϊ�����ʷ����� */
extern void CH543SoftReset( void );                 							/* CH543����λ */
extern void CH543WDTModeSelect( UINT8 mode );	   								/* ���Ź�ģʽѡ�� */
extern void CH543WDTFeed( UINT8 tim );           								/* ���Ź�ι�� */
	
#endif
