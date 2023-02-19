/********************************** (C) COPYRIGHT *******************************
* File Name          : main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/04/28
* Description        : CH543 PD Sink����, �̶�����5V3A��λ
*                      Notice that this example also needs to add TIMER.C file.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0 
********************************************************************************/


/*******************************************************************************/
/* ��غ궨�� */
#define PD_PROT_EXAM 1

/*******************************************************************************/
/* ͷ�ļ����� */
#include <stdio.h>
#include "CH543.H"
#include "DEBUG.H"
#include ".\PD_PROT\PD_PHY.H"
#include ".\PD_PROT\PD_PROT.H"

/********************************************************************************
* Function Name  : main
* Description    : ��ѭ��
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/ 
void main( void ) 
{
	CfgFsys( );							                                        /* 24MHz */
	mInitSTDIO( );						                                        /* UART��ʼ�� */
	

	mDelaymS( 10 );
	printf("CH543D\r\n");
	
	
	PD_PHY_Init( );
	
	
	while( 1 ) 
    {					
        /* ����豸���� */
		if( ( CC1_CTRL & bCC_CMPO ) && ( !( CC2_CTRL & bCC_CMPO ) ) ) 
        {
			UPD_CTRL &= ~bPD_CC_SEL;
			break;
		}
		if( ( CC2_CTRL & bCC_CMPO ) && ( !( CC1_CTRL & bCC_CMPO ) ) ) 
        {
			UPD_CTRL |= bPD_CC_SEL;
			break;
		}
		mDelaymS( 5 );
	}
	
	UPD_CTRL |= bPD_DMA_EN;		//����PD DMA
	PD_PHY_RX_INIT( );			//PD�������״̬
	IE_USBPD = 1;				//�����ж�
	EA = 1;
	
	while( 1 ) 
    {
		mDelaymS( 10 );
	}
}


