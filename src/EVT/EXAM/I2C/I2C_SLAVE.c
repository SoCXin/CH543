/********************************** (C) COPYRIGHT *******************************
* File Name          : I2C_SLAVE.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 I2C Slave �ж�����

��������:֧�ֶ��ֽڷ�������,ʱ���ͬ��24CXXϵ��Page Write,���ݵ�ַ��ʼ��ַ0x00
        START + ������ַ(0x56) + ���ݵ�ַ(0x00) + ����*(N) + STOP

������ȡ:֧�ֶ��ֽڶ�ȡ���ݣ�ʱ���ͬ��24CXXϵ��Random Read,���ݵ�ַ��ʼ��ַΪ0x00
        START + ������ַ(0x56) + ���ݵ�ַ(0x00) + START + ������ַ(0x57) + ����*(N) + STOP
  SCL  ->  P1.6
  SDA  ->  P1.7
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#pragma  NOAREGS

/******************************************************************************/
/* ������������ */
UINT8X I2CS_Buff[ 32 ] = { 0 };
UINT8X I2CS_Buff_S[ 32 ] = { 0 };
UINT16 Recv_len = 0,I2CS_Flag = 0,Recv_Flag = 0;

/*******************************************************************************
* Function Name  : I2CS_Slave_Init
* Description    : Ӳ��I2CS��ʼ������
* Input          : None
* Return         : None
*******************************************************************************/
void I2CS_Slave_Init( void )
{
    UINT8 i;
    
    for( i = 0; i < 32; i++ )
    {
        I2CS_Buff[i] = 0xFF;
        I2CS_Buff_S[i] = i | 0x80;
    }
    
    P1_MOD_OC |= 0xC0;                                                          /* ��©��� */
    P1_DIR_PU |= 0xC0;                                                          /* ʹ������ */
    I2CS_DEV_A = 0x56;                                                          /* �ӻ��豸��ַ */
    I2CS_CTRL = bI2CS_IE_READ | bI2CS_IE_WRITE | bI2CS_IE_ADDR | bI2CS_IE_STASTO | bI2CS_EN;
    IE_I2C = 1;
}

/*******************************************************************************
* Function Name  : I2C_INT( )
* Description    : IIC �жϷ�����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_INT( void ) interrupt INT_NO_I2C using 1
{
    if( I2CS_STAT & bI2CS_IF_DEV_A )
    {
        Recv_len = 0;
        Recv_Flag = 0;
        I2CS_Flag = 0;
    }
    if( ( I2CS_STAT & MASK_I2CS_STAT ) == 3)                                    /* ���յ����ݵ�Ԫ��ַ */    
    {
        I2CS_DATA = *( I2CS_Buff_S + I2CS_ADDR );
    }
    else if( ( I2CS_STAT & MASK_I2CS_STAT ) == 5 )                              /* ���յ������ֽ� */   
    {
        I2CS_Buff[ I2CS_ADDR ] = I2CS_DATA;        
        Recv_Flag = 1;
        Recv_len++;
    }
    else if( ( I2CS_STAT & MASK_I2CS_STAT ) == 7 )
    {
        I2CS_DATA = *( I2CS_Buff_S + I2CS_ADDR );
    }
    else if( (I2CS_STAT & MASK_I2CS_STAT) == 0x0C )                             /*���յ�stop һ�δ������*/
    {
        I2CS_Flag = 1; 
    }
    I2CS_STAT |= 0xF0;                                                          /* ��I2CS�ж� */
}

/*******************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void main( void )
{
    UINT8 i;
    
    /*****************************ϵͳ��س�ʼ��*******************************/
    CfgFsys( );
    mDelaymS( 20 );                                                             /* ������Ƶ�������Լ���ʱ�ȴ��ڲ�ʱ���ȶ� */
    mInitSTDIO( );                                                              /* ����0��ʼ�� */
    
    /* IIC�ӻ���ʼ�� */ 
    I2CS_Slave_Init( );
    printf("I2CS start ...\n");
    
    EA = 1;
    E_DIS = 0;
    
    /*****************************��ѭ��***************************************/
    while( 1 )
    {
        
        /* �жϷ�ʽ�շ�,Ӧ����ʵ��Ӧ�ý����Ż� */
		if(( I2CS_Flag == 1 ) && ( Recv_Flag == 1 ) )
		{
			I2CS_Flag = 0;
			Recv_Flag = 0;
            printf("len %d\n",(UINT16)Recv_len);
            for ( i = 0; i < 32; i++ )
            {
                printf("%02x ",(UINT16)I2CS_Buff[i]);
            }
            printf("\n");
            for ( i = 0; i < 32; i++ )
            {
                I2CS_Buff[i] = 0xFF;
            }
		}
    }
}
