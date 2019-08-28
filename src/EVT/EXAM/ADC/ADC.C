/********************************** (C) COPYRIGHT *******************************
* File Name          : ADC.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 ADC����ʱ������,ADCͨ�����ú���,�ⲿͨ������ʼ��
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */	
#include "ADC.H"
#pragma  NOAREGS

/*******************************************************************************
* Function Name  : ADC_Init
* Description    : ADC ��ʼ������
* Input          : UINT8 AdcClk
                   0 :1024 Fosc cycles for each ADC
                   1 :512  Fosc cycles for each ADC
                   2 :256  Fosc cycles for each ADC
                   3 :128  Fosc cycles for each ADC
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Init( UINT8 AdcClk )
{
    UINT8 dat;
    ADC_CTRL = bADC_EN;                                                         /* ����ADCģ���Դ */
    ADC_CTRL = (ADC_CTRL & ~(bADC_CLK0 | bADC_CLK1)) | AdcClk;                  /* ѡ��ADC�ο�ʱ�� */
    dat = ADC_DAT;                                                              /* �ն� */
    ADC_CTRL |= bADC_IF;                                                        /* ���ADCת����ɱ�־��д1���� */
#if EN_ADC_INT
    IE_ADC = 1;                                                                 /* ����ADC�ж�ʹ�� */
    EA = 1;                                                                     /* �������ж�ʹ�� */
#endif
}

/*******************************************************************************
* Function Name  : ADC_ChSelect
* Description    : ADC ͨ��ѡ��
* Input          : UINT8 ch
                   ch, λ�� 0~13bitΪ�ⲿ12ͨ�����ڲ���Դ��ѹ���ڲ��ο���ѹ
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ChSelect( UINT8 ch )
{
    ADC_CHAN = (ADC_CHAN & ~0x0F) | ch;
    switch(ch)													                /* �������ã�����ÿ�ζ����� */
    {
        case 0:
        case 1:
        case 4:
        case 5:
        case 6:
        case 7:
             P1_MOD_OC &= ~( 1 << ch );							                /* �������� */
             P1_DIR_PU &= ~( 1 << ch );
             break;
        case 2:
             P3_MOD_OC &= ~( 1 << ch ); 						                /* �������� */
             P3_DIR_PU &= ~( 1 << ch );
             break;
        case 8:
        case 9:
             P3_MOD_OC &= ~( 1 << ( ch - 2 ));							        /* �������� */
             P3_DIR_PU &= ~( 1 << ( ch - 2 ));
             break;
        case 0x0A:
        case 0X0B:
             P1_MOD_OC &= ~( 1 << ( ch - 8 ));							        /* �������� */
             P1_DIR_PU &= ~( 1 << ( ch - 8 ));
             break;
    }
}

#if EN_ADC_INT

extern UINT8 GetValueFlag;

/*******************************************************************************
* Function Name  : ADC_ISR( )
* Description    : ADC �жϷ�����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ISR( void )  interrupt INT_NO_ADC
{
    if( ADC_CTRL & bADC_IF )
    {
        ADC_CTRL |= bADC_IF;							                        /* ���ADCת������жϱ�־ */
        GetValueFlag = 1;			
    }	
    ADC_ChSelect( CH0 );							                            /* ѡ����һ����Ҫ�ɼ���ͨ��	*/
}
#endif