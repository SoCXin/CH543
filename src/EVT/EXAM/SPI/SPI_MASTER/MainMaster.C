/********************************** (C) COPYRIGHT *******************************
* File Name          : MainMaster.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 SPI������CH543 SPI�ӻ�ͨѶ,������������,�ӻ�ȡ������
                       �ӻ��ο�MainSlave.C
                       ע�����DEBUG.C/SPI.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



/******************************* Ӳ���ӿڶ��� ***********************************
ʹ��CH543 Ӳ��SPI�ӿ�
         CH543
         P1.4        =       SCS
         P1.5        =       MOSI
         P1.6        =       MISO
         P1.7        =       SCK
********************************************************************************/

/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\SPI\SPI.H"
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
    UINT8 ret,i = 0;
	
    CfgFsys( );																	/* CH543ʱ��ѡ������ */
    mDelaymS( 20 );                                                             /* ����ʱ�Ӻ�,������ʱ�ȶ�ʱ�� */
    mInitSTDIO( );                                                             	/* ����0��ʼ�� */
    
	printf("SPI Master start ...\n");
    SPIMasterModeSet( 3 );														/* SPI����ģʽ����,ģʽ3 */
    SPI_CK_SET( 12 );                                                           /* 12��Ƶ */
    
	while( 1 )
    {
        SCS = 0;                                                               	/* SPI������������ */
        CH543SPIMasterWrite( i );
        mDelaymS( 5 );
        ret = CH543SPIMasterRead( );                                            /* ����SPI�ӻ����ص�����,ȡ������ */
        SCS = 1;
        
		if( ret != ( i ^ 0xff ) )
        {
            printf("Err: %02X  %02X  \n",(UINT16)i,(UINT16)ret);               	/* ��������ڷ������ݵ�ȡ��,��ӡ������Ϣ */
        }
        else
        {
            printf("success %02x\n",(UINT16)i);                                	/* ÿ�ɹ�40�δ�ӡһ�� */
        }
		
        i = i+1;
        mDelaymS( 50 );
    }
}