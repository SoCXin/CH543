/********************************** (C) COPYRIGHT *******************************
* File Name          : Compare.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 ADC�Ƚ���
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */	
#include ".\Compare\Compare.H"
#pragma  NOAREGS

/*******************************************************************************
* Function Name  : CMP_Init
* Description    : �Ƚ���ģ���ʼ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CMP_Init( void )
{
    ADC_CTRL = bADC_EN;                                                         /* ����ADCģ���Դ */
    ANA_CTRL |= bCMP_EN;  					                                    /* ����CMP��Դ */
    ANA_CTRL |= bCMP_CHAN_N;   		                                            /* CM��ѡ��P13 */
    ANA_CTRL &= ~bCMP_CHAN_P;   		                                        /* CP��ѡ����ADC_CHANѡ���ͨ��4 */
    
    P1_MOD_OC &= ~0x18;                                                         /* P1.3 P1.4�������� */
    P1_DIR_PU &= ~0x18;
		
    ADC_CHAN = (1<<4) | (1<<11);							                    /* �����������ͨ���ֱ�Ϊ ch4,ch3 */
    ANA_CTRL |= bCMP_CHAN_X;   		                                            /* COʹ�ܣ������P12 */
    ADC_CTRL |= bADC_IF;                                                        /* ����Ƚϱ�־��д1���� */
#if EN_ADC_INT
    ANA_CTRL |= bCMP_IE;										                /* CMP����ı��ж�ʹ�� */
    PWM_CTRL &=~ bPWM_IE_END;                                                   /* ��PWM�жϵ�ַ���ã����ж���2ѡ1 */
    IE_CMP = 1;                                                                 /* ����CMP�ж�ʹ�� */
    EA = 1;                                                                     /* �������ж�ʹ�� */
#endif
		
}

#if EN_ADC_INT
/*******************************************************************************
* Function Name  : CMP_ISR( )
* Description    : CMP �жϷ�����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CMP_ISR( void )  interrupt INT_NO_CMP
{
	printf("ANA_CTRL=%x\n",(UINT16)ANA_CTRL);
	printf("INT CMP! CMP changes\n");
}
#endif