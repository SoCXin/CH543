/********************************** (C) COPYRIGHT ********************************
* File Name          : DataFlash.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 DataFlash�ֽڶ�д��������
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


#ifndef __DATAFLASH_H__
#define __DATAFLASH_H__

/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"

/***************************** Flash�ռ仮�� ***********************************
*   0x3FFD  ---
*            |                   Code Flash(BOOT���� 1.75K)
*   0x3900  ---
*   0x38FF  ---
*            |                   Data Flash��256��
*   0x3800  ---
*   0x37FF  ---
*            |                   Code Flash���û�������14K��
*   0x0000  ---
*******************************************************************************/

/******************************************************************************/
/* �������� */
/* Code Flash��Data Flash���� */
extern UINT8 FlashErasePage( UINT16 Addr );                                     /* ����ҳ����, ÿ64�ֽ�Ϊһҳ, ��ҳ���������ݱ�Ϊ0x00 */
extern UINT8 FlashProgByte( UINT16 Addr, UINT8 Data );                          /* Flash�ֽڱ�� */
extern UINT8 FlashProgPage( UINT16 Addr, PUINT8X Buf, UINT8 len );              /* ҳ���,����̵�ǰAddr����ҳ */
extern UINT8 FlashReadBuf( UINT16 Addr, PUINT8 buf, UINT16 len );               /* ��Flash(����data��code) */

/* OTP����ReadOnly������ */
extern UINT8  FlashProgOTPbyte( UINT8 Addr, UINT8 Data );                       /* ���ֽ�дOTP����ֻ��0���1,�Ҳ��ɲ��� */
extern UINT32 FlashReadOTPword( UINT8 Addr );                                   /* 4�ֽ�Ϊ��λ��ȡReadOnly������OTP�� */

#endif

/*********************************END OF FILE**********************************/