/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 ADC��ʼ��,ADC�жϺͲ�ѯ��ʽ��ʾ�ⲿͨ���Լ��ڲ�ͨ�����
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */	
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\ADC\ADC.H"

/******************************************************************************/
/* ������������ */
volatile UINT8 GetValueFlag = 0;                                                /* ADC�жϷ�ʽ�ɼ���ɱ�־λ��1��Ч */
#pragma  NOAREGS

/*******************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void main( void )
{
    UINT8 ch;
    
    /*****************************ϵͳ��س�ʼ��*******************************/
    CfgFsys( );                                                                 /* CH543ʱ��ѡ�� */
    mDelaymS( 5 );                                                              /* �Լ���ʱ�ȴ���ʱ�ȶ� */
    mInitSTDIO( );                                                              /* ����0��ʼ�� */
    
    printf("ADC demo start ...\n");
    
    /* ADC��ʼ�� */    
    ADC_Init( 0 );                                                              /* ADC��ʼ��,ѡ�����ʱ�� */
    
    /*****************************��ѭ��***************************************/
    while( 1 )
    {
#if ( EN_ADC_INT == 0 )                                                         /* ��ѯ��ʽ��ʾADCͨ���л��Ͳɼ� */
        /* ѭ���ɼ�ADC 0~13 ͨ�� */
        for( ch=0; ch!=14; ch++ )
        {  
            ADC_ChSelect( ch );                                                 /* ѡ��ͨ�� */
            ADC_StartSample( );                                                 /* �������� */
            while( (ADC_CTRL&bADC_IF) == 0 )                                    /* �ȴ�ת����� */
            {
            }
            ADC_CTRL |= bADC_IF;                                                /* ���־ */
            printf("ch%d=%d\n",(UINT16)ch, (UINT16)ADC_DAT);                    /* ���ADC����ֵ */
        }
        printf("\n");
        mDelaymS( 100 );                                                        /* ģ�ⵥƬ������������ */
#else                                                                           /* �жϷ�ʽ��ʾADCͨ���л��Ͳɼ�����ͨ��0Ϊ�� */
        ADC_StartSample( );                                                     /* �������� */
        mDelaymS( 10 );                                                         /* ģ�ⵥƬ������������ */
        if( GetValueFlag )                                                      /* ͨ���ɼ���ɱ�־ */
        {
            printf("ch0=%d\n",(UINT16)ADC_DAT);                                 /* ���ADC����ֵ */
        }
        mDelaymS( 100 );                                                        /* ģ�ⵥƬ������������ */
#endif
    }
}