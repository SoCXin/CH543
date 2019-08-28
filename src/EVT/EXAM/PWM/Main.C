/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 PWM��ʼ��,ռ�ձ�����,PWMĬ�ϵ�ƽ����
*                      ֧���жϷ�ʽ�޸�PWMռ�ձ�
*                      ����           ����
*                      P15            PWM0
*                      P34            PWM1
*                      P16            PWM2
*                      P14            PWM3
                       ע�����DEBUG.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\PWM\PWM.H"
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
    CfgFsys( );																	/* CH543ʱ��ѡ������ */
    mDelaymS( 5 );																/* ����ʱ�Ӻ�,������ʱ�ȶ�ʱ�� */
    mInitSTDIO( );                                                             	/* ����0��ʼ�� */
    printf("PWM Demo start ...\n");
	
    SetPWM8Bit( );																/* PWM���ݿ���Ϊ8λ */
    
	/* ʱ��Ƶ������ */
    SetPWMClkDiv( 4 );															/* PWMʱ������,FREQ_SYS/4 */
    SetPWMCycle_H( 1 );
    SetPWMCycle_L( 44 );														/* PWM_CYCLE=FREQ_SYS/4/(cyc_h*256+cyc_l) */
    
	/* PWM0 PWM1�����Ч��������(��ѡ) */
    PWM0OutPolarLowAct();
    PWM1OutPolarHighAct();
    
	/* ��ʼռ�ձ����� */
    SetPWM0Dat( 50 );														                  			         //���ռ�ձ�=dat/PWM_CYCLE
    SetPWM1Dat( 100 );
    SetPWM2Dat( 150 );
    SetPWM3Dat( 200 );
	
    /* ����ͨ�� */
    PWM_SEL_CHANNEL( CH0 | CH1 | CH2 | CH3, Enable );                 			/* ���ʹ�� */
#ifdef PWM_INTERRUPT
    PWMInterruptEnable( );
#endif

    while( 1 )
    {
		/*********************************************************************/
		/* ��ѭ������ */
		
    }
}