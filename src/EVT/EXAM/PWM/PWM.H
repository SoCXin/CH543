/********************************** (C) COPYRIGHT *******************************
* File Name          : PWM.H
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 PWM�������ѡ���жϴ���(PWM ѭ�����ڽ����ж�)
*                      ����           ����
*                      P15            PWM0
*                      P34            PWM1
*                      P16            PWM2
*                      P14            PWM3
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



#ifndef __PWM_H__
#define __PWM_H__

/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"

/*******************************************************************************/
/* ��غ궨�� */

/* PWM�ж�ʹ�� */
#define PWM_INTERRUPT

/* PWMͨ��(�������) */
#define   CH0        				0x01
#define   CH1       				0x02
#define   CH2        				0x04
#define   CH3        				0x08

/* ���ʹ��״̬ */
#define  Disable					0x00										/* �ر���� */
#define  Enable      				0x01										/* ʹ����� */

/* �ⲿ���ú㶨�� */
#define SetPWMClkDiv( n )			PWM_CK_SE = n                            	/* PWMʱ������,FREQ_SYS/n */  
#define SetPWM12Bit( )				PWM_CTRL2 |= bPWM_MOD_12BIT              	/* PWM���ݿ���Ϊ12λ,��PWM0��PWM1���� */
#define SetPWM8Bit( ) 	      		PWM_CTRL2 &= ~bPWM_MOD_12BIT             	/* PWM���ݿ���Ϊ8λ */
#define SetPWMCycle_L( cyc_l ) 	   	PWM_CYCLE_L = cyc_l							/* ����PWM����ֵ���ֽ� */
#define SetPWMCycle_H( cyc_h ) 	   	PWM_CYCLE_H = cyc_h          				/* ����PWM����ֵ���ֽڵ�4λ */
#define PWM0OutPolarHighAct( )    	PWM_CTRL &= ~bPWM0_POLAR                 	/* PWM0���Ĭ�ϵ�,����Ч(Ĭ��) */
#define PWM0OutPolarLowAct( )     	PWM_CTRL |= bPWM0_POLAR                  	/* PWM0���Ĭ�ϸ�,����Ч */
#define PWM1OutPolarHighAct( )    	PWM_CTRL &= ~bPWM1_POLAR                 	/* PWM1���Ĭ�ϵ�,����Ч(Ĭ��) */         
#define PWM1OutPolarLowAct( )     	PWM_CTRL |= bPWM1_POLAR                  	/* PWM1���Ĭ�ϸ�,����Ч */
#define SetPWM0Dat( dat )          	PWM_DATA0 = dat                          	/* ����PWM0���ռ�ձ� */
#define SetPWM1Dat( dat )          	PWM_DATA1 = dat                          	/* ����PWM1���ռ�ձ� */
#define SetPWM2Dat( dat )          	PWM_DATA2 = dat                          	/* ����PWM2���ռ�ձ� */
#define SetPWM3Dat( dat )          	PWM_DATA3 = dat                          	/* ����PWM3���ռ�ձ� */

/*******************************************************************************/
/* �������� */
extern void PWM_SEL_CHANNEL( UINT8 Channel, UINT8 NewState );                	/* PWMͨ�����ʹ��,����IO�˿����� */
#ifdef PWM_INTERRUPT
extern void PWMInterruptEnable( void );                                         /* ʹ��PWM��������ж� */
#endif

#endif