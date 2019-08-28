/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 11ͨ������������ʾ
*                      CH0~CH2,�ֱ��ӦP10 P11 P32
*                      CH4~CH11,�ֱ��ӦP14~P17 P36 P37 P12 P13
                       ע�����DEBUG.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\TouchKey\TouchKey.H"
#pragma  NOAREGS

/*******************************************************************************/
/* �������� */
UINT16 PowerValue[ 16 ];                                             			/* ���津�������ϵ�δ����ֵ */
volatile UINT16 Press_Flag = 0;                                                	/* ���±�־λ */
UINT8C CPW_Table[ 16 ] = { 30, 30, 30, 30, 30, 30, 30, 30,                      /* ��������йصĲ���,�ֱ��Ӧÿ������ */
						   30, 30, 30, 30, 30, 30, 30, 30, };
						 
/********************************************************************************
* Function Name  : ABS
* Description    : ����������ֵ�ľ���ֵ
* Input          : a,b
* Output         : None
* Return         : ��ֵ����ֵ
********************************************************************************/
UINT16 ABS( UINT16 a, UINT16 b )
{
    if( a > b )
    {
        return ( a - b );
    }
    else
    {
        return ( b - a );
    }
}

/********************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void main( void )
{
    UINT8 i = 100;
    UINT8 ch;
    UINT16 value;
    UINT16 err;																	/* ����ģ��仯��ֵ */
    
    memset( KeyBuf, 0, sizeof( KeyBuf ) );	
    CfgFsys( );                                                                	/* CH543ʱ��ѡ������ */
    mDelaymS( 20 );																/* ����ʱ�Ӻ�,������ʱ�ȶ�ʱ�� */
    mInitSTDIO( );                                                             	/* ����0��ʼ�� */
    
	printf("TouchKey demo start ...\n");
    TouchKey_Init( );
    Press_Flag = 0;                                                            	/* �ް������� */
    
    mDelaymS( 100 );	
        
    /* ��ȡ������ֵ */
    for( ch = 4; ch != 8; ch++ )
    {
        PowerValue[ ch ] = Default_TouchKey( ch, CPW_Table[ ch ] );
        printf("Y%d",PowerValue[ ch ]);
    }
    printf("\n");
	
    while( 1 )
    {
        while( i )																/* ����ʼֵ,����ʡ */
        {
            for( ch = 4; ch != 8; ch++ )
            {
                TouchKeySelect( ch, CPW_Table[ ch ] );
                i--;
            }
        }
		
		/* ������� */
        for( ch = 4; ch != 8; ch++ )
        {
            value = TouchKeySelect( ch, CPW_Table[ ch ]  );
            err = ABS( PowerValue[ ch ], value );
            
			if( err > DOWM_THRESHOLD_VALUE )									/* ��ֵ������ֵ����Ϊ���� */
            {
                if( ( Press_Flag & ( 1 << ch ) ) == 0 )                         /* ˵���ǵ�һ�ΰ��� */
                {
                    printf("ch %d pressed,value:%d\n",(UINT16)ch, value);
                }
                Press_Flag |= ( 1 << ch );
            }
            else if( err < UP_THRESHOLD_VALUE )                                	/* ˵��̧�����δ���� */
            {
                if( Press_Flag & ( 1 << ch ) )									/* ��̧�� */
                {
                    Press_Flag &= ~( 1 << ch );
                    printf("ch %d up,value:%d\n",(UINT16)ch, value);
                }
            }
        }
    }
}