/********************************** (C) COPYRIGHT *******************************
* File Name          : SPI.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 SPI������ģʽ�ӿں���
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



#ifndef __SPI_H__
#define __SPI_H__

/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"

/*******************************************************************************/
/* ��غ궨�� */
//#define  SPI_INTERRUPT                                                        	/* �ж�ʹ��(��Slaveģʽ) */
#define  SPI_CK_SET( n ) 		( SPI0_CK_SE = n )								/* SPIʱ�����ú��� */

/*******************************************************************************/
/* �������� */

/* Master��غ��� */
extern void  SPIMasterModeSet( UINT8 mode );									/* SPI����ģʽ��ʼ�� */
extern void  CH543SPIMasterWrite( UINT8 dat );                                  /* CH543Ӳ��SPIд����,����ģʽ */
extern UINT8 CH543SPIMasterRead( );                                            	/* CH543Ӳ��SPI0������,����ģʽ */

/* Slave��غ��� */
extern void  SPISlvModeSet( );                                                	/* SPI�ӻ�ģʽ��ʼ�� */
extern void  CH543SPISlvWrite( UINT8 dat );                                     /* CH543Ӳ��SPIд����,�ӻ�ģʽ */
extern UINT8 CH543SPISlvRead( );                                               	/* CH543Ӳ��SPI0������,�ӻ�ģʽ */

#endif