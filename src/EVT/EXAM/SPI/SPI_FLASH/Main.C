/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 SPI Flash��д������ʾ
                       ע�����DEBUG.C/SPI.C/SPIFlash.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\SPI\SPI_FLASH\SPIFlash.H"
#pragma  NOAREGS

/*******************************************************************************/
/* �������� */
UINT8X buf[64];

/********************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void main( void )
{
    UINT16X i;
	
    CfgFsys( );																	/* CH543ʱ��ѡ������ */
    mDelaymS( 20 );																/* ����ʱ�Ӻ�,������ʱ�ȶ�ʱ�� */
    mInitSTDIO( );                                                             	/* ����0��ʼ�� */
    printf("SPI Flash demo start ...\n");
    
    for( i = 0; i != 64; i++ )
    {
        buf[ i ] = i;
    }
	
    SPIFlash_Init( );
    EraseExternal4KFlash_SPI( 0 );
    BlukWriteExternalFlash_SPI(3, 64, buf );
    BlukReadExternalFlash_SPI( 0, 64, buf );
    
	for( i = 0; i != 64; i++ )
    {
        printf("%02x ",(UINT16)buf[ i ]);
    }
    printf("done\n");
	
    while( 1 )
    {
		/*********************************************************************/
		/* ��ѭ������ */
		
    }
}