/********************************** (C) COPYRIGHT *******************************
* File Name          : GPIO.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 GPIO��غ���
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */
#include ".\GPIO\GPIO.H"
#pragma  NOAREGS

/*******************************************************************************
* Function Name  : GPIO_Init
* Description    : GPIO�˿ڳ�ʼ������
* Input          : PORTx:1��3
*                  PINx:λ��,ÿ��λ��Ӧ��Port��һ������
*                  MODEx:
*                        0: ��������ģʽ,����û����������
*                        1: �������ģʽ,���жԳ���������,��������������սϴ����
*                        2: ��©���,֧�ָ�������,����û����������
*                        3: ׼˫��ģʽ(��׼ 8051),��©���,֧������,��������������(Ĭ��ģʽ)
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Init( UINT8 PORTx, UINT8 PINx, UINT8 MODEx )
{
    UINT8 Px_DIR_PU,Px_MOD_OC;
    
    switch( PORTx )                                                               /* ������ʼֵ */
    {
        case PORT1:
            Px_MOD_OC = P1_MOD_OC;
            Px_DIR_PU = P1_DIR_PU;
            break;
        case PORT3:
            Px_MOD_OC = P3_MOD_OC;
            Px_DIR_PU = P3_DIR_PU;
            break;
        default :
            break;
    }
    switch( MODEx )
    {
        /* ��������ģʽ������û���������� */
        case MODE0:
            Px_MOD_OC &= ~PINx;
            Px_DIR_PU &= ~PINx;
            break;
        /* �������ģʽ�����жԳ�������������������������սϴ���� */
        case MODE1:
            Px_MOD_OC &= ~PINx;
            Px_DIR_PU |= PINx;
            break;
        /* ��©�����֧�ָ������룬����û���������� */
        case MODE2:
            Px_MOD_OC |= PINx;
            Px_DIR_PU &= ~PINx;
            break;
        /* ׼˫��ģʽ(��׼ 8051)����©�����֧�����룬�������������� */
        case MODE3:
            Px_MOD_OC |= PINx;
            Px_DIR_PU |= PINx;
            break;
        default :
            break;
    }
    switch( PORTx )                                                               /* ��д */
    {
        case PORT1:
            P1_MOD_OC = Px_MOD_OC;
            P1_DIR_PU = Px_DIR_PU;
            break;
        case PORT3:
            P3_MOD_OC = Px_MOD_OC;
            P3_DIR_PU = Px_DIR_PU;
            break;
        default :
            break;
    }
}

/*******************************************************************************
* Function Name  : GPIO_INT_Init
* Description    : ������ P17_L��P15_L��P14_L��P13_L��RST_H��P31_L��RXD0_L ��չ��
*                  �ŵ��ⲿ�ж�,ͬʱ����������C51�� INT1_L��INT0_L ���ⲿ�жϴ���
*                  (RXD0_L�������ĸ�����ȡ���������Ƿ�ӳ��)
* Input          : IntSrc:��9���ⲿ�ж�,��λ���ʾ,���嶨���GPIO.H
*                  Mode��0����ƽģʽ   1������ģʽ (ע����չ���ŵ��ж�ģʽ��ͳһ���õ�)
*                  NewState��0���رն�Ӧ�ⲿ�ж�ʹ��  1��������Ӧ�ⲿ�ж�
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_INT_Init( UINT16 IntSrc,UINT8 Mode,UINT8 NewState )
{
    /* �жϴ���ģʽ���� */
    if( Mode == INT_EDGE )                                                      /* ���ش���ģʽ */
    {
        if( IntSrc & 0x7F )                                                     /* ������չ�ж� */
        {
            SAFE_MOD = 0x55;
            SAFE_MOD = 0xAA;
            GPIO_IE |= bIE_IO_EDGE;
            SAFE_MOD = 0x00;
        }
        if(IntSrc & INT_INT0_L)                                                 /* �����ⲿ�ж�0 */
        {
            IT0 = 1;
        }
        if(IntSrc & INT_INT1_L)                                                 /* �����ⲿ�ж�1 */
        {
            IT1 = 1;
        }
    }
    else                                                                        /* ��ƽ����ģʽ */
    {
        if( IntSrc & 0x7F )                                                     /* ������չ�ж� */
        {
            SAFE_MOD = 0x55;
            SAFE_MOD = 0xAA;
            GPIO_IE &= ~bIE_IO_EDGE;
            SAFE_MOD = 0x00;
        }
        if( IntSrc & INT_INT0_L )                                               /* �����ⲿ�ж�0 */
        {
            IT0 = 1;
        }
        if( IntSrc & INT_INT1_L )                                               /* �����ⲿ�ж�1 */
        {
            IT1 = 1;
        }
    }
    /* �ж�ʹ��״̬ */
    if( NewState == Enable )                                                    /* �����ⲿ�ж� */
    {
        SAFE_MOD = 0x55;
        SAFE_MOD = 0xAA;
        GPIO_IE |= ( (UINT8)IntSrc & 0x7F );
        SAFE_MOD = 0x00;
        if( IntSrc & INT_INT0_L )                                               /* �����ⲿ�ж�0 */
        {
            EX0 = 1;
        }
        if( IntSrc & INT_INT1_L )                                               /* �����ⲿ�ж�1 */
        {
            EX1 = 1;
        }
        if( GPIO_IE & 0x7F )
        {
            IE_GPIO = 1;                                                        /* ������չGPIO�ж� */
        }
        EA = 1;                                                                 /* �������ж� */
    }
    else                                                                        /* �رն�Ӧ�ⲿ�ж� */
    {
        SAFE_MOD = 0x55;
        SAFE_MOD = 0xAA;
        GPIO_IE &= ~( (UINT8)IntSrc & 0x7F );
        SAFE_MOD = 0x00;
        if( IntSrc & INT_INT0_L )                                               /* �����ⲿ�ж�0 */
        {
            EX0 = 0;
        }
        if(IntSrc & INT_INT1_L)                                                 /* �����ⲿ�ж�1 */
        {
            EX1 = 0;
        }
        if( ( GPIO_IE & 0x7F ) == 0 )
        {
            IE_GPIO = 0;                                                        /* �ر���չGPIO�ж� */
        }
    }
}

/*******************************************************************************
* Function Name  : GPIO_ISR
* Description    : P17��P15��P14��P13��RST��P31��RXD0 �����ⲿ�жϷ�����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_EXT_ISR( void ) interrupt INT_NO_GPIO
{
    mDelaymS( 10 );
    printf("GPIO int\n");
}

/*******************************************************************************
* Function Name  : GPIO_STD0_ISR
* Description    : INT0(P32) �����ⲿ�жϷ�����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_STD0_ISR( void ) interrupt INT_NO_INT0
{
    mDelaymS( 10 );
    printf("P32 Falling\n");

}

/*******************************************************************************
* Function Name  : GPIO_STD1_ISR
* Description    : INT1(P33) �����ⲿ�жϷ�����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_STD1_ISR( void ) interrupt INT_NO_INT1
{
    mDelaymS( 10 );
    printf("P33 Falling\n");

}