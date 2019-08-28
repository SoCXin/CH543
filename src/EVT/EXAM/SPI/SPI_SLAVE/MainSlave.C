/********************************** (C) COPYRIGHT *******************************
* File Name          : MainSlave.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 SPI�豸������ʾ������SPI�������������շ����ӻ���ȡ����������ȡ��
                       Ȼ���͸�����
                       ע�����DEBUG.C/SPI.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



/******************************** Ӳ���ӿڶ��� **********************************
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
    mDelaymS( 5 );                                                              /* ����ʱ�Ӻ�,������ʱ�ȶ�ʱ�� */
    mInitSTDIO( );                                                             	/* ����0��ʼ�� */
    
	printf("SPI Slave start ...\n");
    SPISlvModeSet( );                                                          	/* SPI�ӻ�ģʽ���� */
    
	while( 1 )
    {
#ifndef SPI_INTERRUPT
        ret = CH543SPISlvRead( );                                               /* ��������CS=0 */
        CH543SPISlvWrite( ret ^ 0xFF );                                         /* SPI�ȴ�����������ȡ��,SPI ����ÿ�ζ�֮ǰ�Ƚ�CS=0,�����CS=1 */
        printf("Read#%02x\n",(UINT16)ret);
#endif
    }
}