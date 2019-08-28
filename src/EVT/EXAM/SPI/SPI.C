/********************************** (C) COPYRIGHT *******************************
* File Name          : SPI.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 SPI������ģʽ�ӿں���
* ע: Ƭѡ��Чʱ,�ӻ����Զ�����SPI0_S_PRE��Ԥ��ֵ��������λ������,������ÿ�����Ƭѡ
* ��Чǰ��SPI0_S_PRE�Ĵ���д��Ԥ��ֵ,�����������˶����׸������ֽ�,����ʱע����������
* ȡ��SPI0_S_PRE�����ֵ����һ��S0_IF_BYTE�ж�;
* ���Ƭѡ����Ч����Ч,�ӻ����Ƚ��з��͵Ļ�,��ð���������ֽڷŵ�SPI0_S_PRE�Ĵ�����;
* S����Ѿ�����Ƭѡ��Ч�Ļ�,��������ʹ��SPI0_DATA�Ϳ���.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\SPI\SPI.H"
#pragma  NOAREGS

/********************************************************************************
* Function Name  : SPIMasterModeSet( UINT8 mode )
* Description    : SPI����ģʽ��ʼ��
* Input          : UINT8 mode
* Output         : None
* Return         : None
********************************************************************************/
void SPIMasterModeSet( UINT8 mode )
{
    SCS = 1;
    P1_MOD_OC &= ~( bSCS | bMOSI | bSCK );
    P1_DIR_PU |= ( bSCS | bMOSI | bSCK );										/* SCS,MOSI,SCK��������� */
    P1_MOD_OC |= bMISO;                                                       	/* MISO �������� */
    P1_DIR_PU |= bMISO;
    SPI0_SETUP = 0;                                                           	/* Masterģʽ,��λ��ǰ */
    
	if( mode == 0 )
    {
        SPI0_CTRL = ( bS0_MOSI_OE | bS0_SCK_OE );								/* ģʽ0 */
    }
    else if( mode == 3 )
    {
        SPI0_CTRL = ( bS0_MOSI_OE | bS0_SCK_OE | bS0_MST_CLK );					/* ģʽ3 */
    }
}

/********************************************************************************
* Function Name  : CH543SPIMasterWrite( UINT8 dat )
* Description    : CH543Ӳ��SPIд����,����ģʽ
* Input          : UINT8 dat   ����
* Output         : None
* Return         : None
********************************************************************************/
void CH543SPIMasterWrite( UINT8 dat )
{
    SPI0_DATA = dat;
    while( S0_FREE == 0 );														/* �ȴ�������� */
}

/********************************************************************************
* Function Name  : CH543SPIMasterRead( void )
* Description    : CH543Ӳ��SPI0������,����ģʽ
* Input          : None
* Output         : None
* Return         : SPI0_DATA
********************************************************************************/
UINT8 CH543SPIMasterRead( void )
{
    SPI0_DATA = 0xff;
    while( S0_FREE == 0 );
    return SPI0_DATA;
}

/********************************************************************************
* Function Name  : SPISlvModeSet( void )
* Description    : SPI�ӻ�ģʽ��ʼ��
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void SPISlvModeSet( void )
{
    P1_MOD_OC &= ~( bSCS | bMOSI | bSCK );										/* SCS,MOSI,SCK �������� */
    P1_DIR_PU &= ~( bSCS | bMOSI | bSCK );
    P1_MOD_OC &= ~bMISO;                                                      	/* MISO������� */
    P1_DIR_PU |= bMISO;
    SPI0_S_PRE = 0x66;                                                        	/* Ԥ��ֵ,����ֵ */
    SPI0_SETUP = bS0_MODE_SLV;                                                	/* Slvģʽ,��λ��ǰ */
    SPI0_CTRL = bS0_MISO_OE;                                                  	/* MISO ���ʹ�� */
#ifdef SPI_INTERRUPT
    SPI0_SETUP |= bS0_IE_FIRST | bS0_IE_BYTE;
    IE_SPI0 = 1;
    EA = 1;
#endif
}

/********************************************************************************
* Function Name  : CH543SPISlvWrite( UINT8 dat )
* Description    : CH543Ӳ��SPIд����,�ӻ�ģʽ
* Input          : UINT8 dat   ����
* Output         : None
* Return         : None
********************************************************************************/
void CH543SPISlvWrite( UINT8 dat )
{
    SPI0_DATA = dat;
    while( S0_FREE == 0 );
}

/********************************************************************************
* Function Name  : CH543SPISlvRead( void )
* Description    : CH543Ӳ��SPI0������,�ӻ�ģʽ
* Input          : None
* Output         : None
* Return         : SPI0_DATA
********************************************************************************/
UINT8 CH543SPISlvRead( void )
{
    while( S0_FREE == 0 );
    return SPI0_DATA;
}

#ifdef SPI_INTERRUPT
/********************************************************************************
* Function Name  : SPIInterrupt( void )
* Description    : SPI�жϷ������,ʹ�üĴ�����1
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void SPIInterrupt( void ) interrupt INT_NO_SPI0 using 1       
{
    UINT8 dat;
	
    dat = CH543SPISlvRead( );
    CH543SPISlvWrite( dat ^ 0xFF );
	
#if DE_PRINTF
    printf("Read#%02x\n",(UINT16)dat);
#endif
}

#endif