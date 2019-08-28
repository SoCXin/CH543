/********************************** (C) COPYRIGHT *******************************
* File Name          : TIMER.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 Time
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



#ifndef __TIMER_H__
#define __TIMER_H__

/*******************************************************************************/
/* ͷ�ļ����� */
#include "Debug.H"

/*******************************************************************************/
/* ��غ궨�� */
#ifdef  PD_PROT_EXAM
#define Timer0_INTERRUPT        1                                              	/* ѡ��Timer0�жϷ�ʽ */
#define Timer1_INTERRUPT        0                                              	/* ѡ��Timer1�жϷ�ʽ */
#else
#define Timer0_INTERRUPT        0                                              	/* ѡ��Timer0�жϷ�ʽ */
#define Timer1_INTERRUPT        1                                              	/* ѡ��Timer1�жϷ�ʽ */
#endif
#define Timer2_INTERRUPT        0                                              	/* ѡ��Timer2�жϷ�ʽ */
#define T2_CAP                  0                                              	/* ѡ��Timer2��׽ģʽ */

/* CH543 Timer0���( bTMR_CLKͬʱӰ��Timer0&1&2,ʹ��ʱҪע�� (����ʱʹ�ñ�׼ʱ��) ) */
#define mTimer0Clk12DivFsys( ) ( T2MOD &= ~bT0_CLK )                            /* ��ʱ��,ʱ��=Fsys/12 T0��׼ʱ�� */
#define mTimer0ClkFsys( )      ( T2MOD |= bTMR_CLK | bT0_CLK )                  /* ��ʱ��,ʱ��=Fsys */
#define mTimer0Clk4DivFsys( )  ( T2MOD &= ~bTMR_CLK; T2MOD |= bT0_CLK )         /* ��ʱ��,ʱ��=Fsys/4(��ʱ��ͬ������DEBUG.C��mInitSTDIO) */
#define mTimer0CountClk( )     ( TMOD |= bT0_CT )                               /* ѡ�����ڼ�����ģʽ(T0����(P34)���½�����Ч) */

/* CH543 Timer1���(DEBUG.C��mInitSTDIOʹ��T1ģʽ2) */
#define mTimer1Clk12DivFsys( ) ( T2MOD &= ~bT1_CLK )                            /* ��ʱ��,ʱ��=Fsys/12  T1��׼ʱ�� */
#define mTimer1ClkFsys( )      ( T2MOD |= bTMR_CLK | bT1_CLK )                  /* ��ʱ��,ʱ��=Fsys */
#define mTimer1Clk4DivFsys( )  ( T2MOD &= ~bTMR_CLK; T2MOD |= bT1_CLK )         /* ��ʱ��,ʱ��=Fsys/4 */
#define mTimer1CountClk( )     ( TMOD |= bT1_CT )                               /* ѡ�����ڼ�����ģʽ(T1����(P35)���½�����Ч) */

/* CH543 Timer2��� */
#define mTimer2Clk12DivFsys( ) { T2MOD &= ~ bT2_CLK; C_T2 = 0; }                /* ��ʱ��,ʱ��=Fsys/12 T2��׼ʱ�� */
#define mTimer2ClkFsys( )      { T2MOD |= (bTMR_CLK | bT2_CLK ); C_T2 = 0; }    /* ��ʱ��,ʱ��=Fsys */
#define mTimer2Clk4DivFsys( )  { T2MOD &= ~bTMR_CLK; T2MOD |= bT2_CLK; C_T2 = 0; }	/* ��ʱ��,ʱ��=Fsys/4(��ʱ��ͬ������DEBUG.C��mInitSTDIO) */
#define mTimer2CountClk( )     { C_T2 = 1; }                                    /* ѡ�����ڼ�����ģʽ(T2����(P10)���½�����Ч) */
#define mTimer2OutCTL( )       ( T2MOD |= T2OE )                                /* T2���  Ƶ��TF2/2 */   

/*******************************************************************************/
/* �������� */
extern UINT8 mTimer_x_ModInit( UINT8 x, UINT8 mode );
extern void  mTimer_x_SetData( UINT8 x, UINT16 dat );
extern void  CAP2Init( UINT8 mode );
extern void  CAP1Init( UINT8 mode );

#endif
