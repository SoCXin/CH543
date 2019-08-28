/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 GPIO������ʾ: ��ͨ�����������; �жϴ���ģʽ
                       ע�����DEBUG.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\GPIO\GPIO.H"
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
    /*****************************ϵͳ��س�ʼ��*******************************/
    CfgFsys( );                                                                 /* CH543ʱ��ѡ������ */
    mDelaymS( 20 );
    mInitSTDIO( );                                                              /* ����0��ʼ�� */
    printf("GPIO demo start ...\n");
    
    /* ����GPIO */
    GPIO_Init( PORT1,PIN3,MODE3 );                                              /* P13�������� */
    GPIO_Init( PORT1,PIN4,MODE3 );                                              /* P14�������� */
    GPIO_Init( PORT1,PIN5,MODE3 );                                              /* P15�������� */
    GPIO_Init( PORT1,PIN7,MODE3 );                                              /* P17�������� */
    GPIO_Init( PORT3,PIN1,MODE3 );                                              /* P31�������� */
    GPIO_Init( PORT3,PIN2,MODE3 );                                              /* P32(INT0)�������� */
    GPIO_Init( PORT3,PIN3,MODE3 );                                              /* P33(INT1)�������� */
    
    /* �����ⲿ�ж� */
    GPIO_INT_Init( ( INT_P15_L | INT_P17_L | INT_INT0_L | INT_INT1_L ), INT_EDGE, Enable);
    
    /*****************************��ѭ��***************************************/
    while( 1 );
    
}