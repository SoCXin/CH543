/********************************** (C) COPYRIGHT *******************************
* File Name          : ADC.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 ADC����ʱ������,ADCͨ�����ú���,�ⲿͨ������ʼ��;
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


#ifndef __ADC_H__
#define __ADC_H__

/******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"

/******************************************************************************/
/* ��غ궨�� */

/* ADC�ж�ʹ�ܶ��� */
#define  EN_ADC_INT                     0                                       /* ADC�ж�ʹ�ܿ��� */

/* ADCͨ������ */
#define  CH0                            0		                                /* P1.0 */
#define  CH1                            1		                                /* P1.1 */
#define  CH2                            2		                                /* P3.2 */
#define  CH3                            3		                                /* RST*25% */
#define  CH4                            4		                                /* P1.4 */
#define  CH5                            5		                                /* P1.5 */
#define  CH6                            6		                                /* P1.6 */
#define  CH7                            7		                                /* P1.7 */
#define  CH8                            8		                                /* P3.6 */
#define  CH9                            9		                                /* P3.7 */
#define  CH10                           0x0A                                    /* P1.2 */
#define  CH11                           0x0B                                    /* P1.3 */
#define  CH12                           0x0C                                    /* VDD12*25% */
#define  CH13                           0x0D                                    /* VREF(Լ1.2V; ����������) */
#define  CHALL                          0xFFFF

/* ���ٵ��ú궨�� */
#define  ADC_ExChannelSelect( ch )      ADC_CHAN = ADC_CHAN & ~0x0F | ch        /* ѡ��ADCͨ��: 0~13 */
#define  ADC_StartSample( )             ADC_CTRL |= bADC_START                  /* ����һ��ADC���� */

/******************************************************************************/
/* �������� */
extern void ADC_Init( UINT8 AdcClk );                                           /* ADCͨ����ʼ�� */
extern void ADC_ChSelect( UINT8 ch );                                           /* ADCͨ��ѡ�� */

#endif

/*********************************END OF FILE**********************************/