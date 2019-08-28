/********************************** (C) COPYRIGHT *******************************
* File Name          : TouchKey.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 TouchKey��������
*                      CH0~CH2,�ֱ��ӦP10 P11 P32
*                      CH4~CH11,�ֱ��ӦP14~P17 P36 P37 P12 P13
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


#ifndef __TOUCHKEY_H__
#define __TOUCHKEY_H__

/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"

/*******************************************************************************/
/* ��غ궨�� */
#define   EN_ADC_INT                    0
#define   DOWM_THRESHOLD_VALUE          1000                     				/* ������ֵ���� */
#define   UP_THRESHOLD_VALUE            50                       				/* ̧����ֵ */
#define   KEY_BUF_LEN                   8                       				/* ÿ��KEY������Ӧ���˲���������С(���޸���Ч) 20 */
#define   KEY_BUF_LOST                  1                        				/* �����ǰ��ֱ������ֽ���(���޸���Ч) 5 */
#define   MASK_ADC_CHAN                 0x0F

/*******************************************************************************/
/* �������� */
extern UINT16I KeyBuf[ 12 ][ KEY_BUF_LEN ];

/*******************************************************************************/
/* �������� */
extern void TouchKey_Init( void );
extern UINT16 TouchKeySelect( UINT8 ch, UINT8 cpw );
extern UINT16 Default_TouchKey( UINT8 ch, UINT8 cpw );

#endif