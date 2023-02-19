/********************************** (C) COPYRIGHT *******************************
* File Name          : PD_PORT.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/04/28
* Description        : 
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0 
********************************************************************************/


/*******************************************************************************/
/* ͷ�ļ����� */
#include <stdio.h>
#include "CH543.H"
#include "DEBUG.H"
#include ".\PD_PROT\PD_PHY.H"
#include ".\PD_PROT\PD_PROT.H"

/*******************************************************************************/
/* ȫ�ֱ������� */
_Union_Fixed	*Fixed;

/********************************************************************************
* Function Name  : PD_PROT_HANDLE
* Description    : PD Э�����Ϣ������ʱ�Ѿ�������GoodCRC��Ϣ��δ���ͣ�
					���Դ˴����ɵ���Ϣ��Ҫ�趨������ʱ
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/ 
void PD_PROT_HANDLE( void )
{
	PD_PHY_Stat.MsgCnt = 0;
	Header = PD_RX_BUF;
	
	if( Header->Struct.Extended == 1 ) 
    {
        return;		                                                            // Extended Message
    }    
	if( Header->Struct.NDO ) 
    {						
        /* Data Message */
		switch( Header->Struct.MsgType ) 
        {
			case SRCCap:
				
				Header = PD_TX_BUF;			                                    //����Request��Ϣ
				Fixed = &PD_TX_BUF[ 2 ];
			
				HeaderAutoFill( );
				Header->Struct.NDO = 1;
				Header->Struct.MsgType = Request;
				Fixed->Data = 0x2CB10411;
			
				PD_PHY_Stat.MsgCnt = 4;		                                    //��λms
				PD_PHY_Stat.MsgLen = 6;
			
				break;
		}
	}
	else 
    {											
        /* Control Message */
		
	}
}
