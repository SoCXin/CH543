/********************************** (C) COPYRIGHT *******************************
* File Name          : PD_PHY.C
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
#include "Timer.H"
#include ".\PD_PROT\PD_PHY.H"
#include ".\PD_PROT\PD_PROT.H"

/*******************************************************************************/
/* ȫ�ֱ������� */
xdata UINT8 PD_RX_BUF[ 30 ];		//����Buffer
xdata UINT8 PD_TX_BUF[ 30 ];		//����Buffer
xdata UINT8 PD_GCRC_BUF[ 2 ];		//����GoodCRCʹ�õ�����Buffer

_PD_PHY_STAT_st  PD_PHY_Stat;		//PD���ò��������ṹ��
_Union_Header	*Header;			//Header��Ϣ����ָ��

/********************************************************************************
* Function Name  : PD_PHY_ISR
* Description    : PD�жϴ�����
					������Ϣ�ɹ����ظ�GoodCRC������Э��㴦��
					������Ϣ�ɹ�������Ҫ��ȡGoodCRC��������ʱ���ȴ�
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/ 
void PD_PHY_ISR( void ) interrupt INT_NO_USBPD using 1
{
	
	/* ���յ���λ��Ϣ�ж� */
	if( PIF_RX_RST ) 
    {
		printf("RST");
		
		/* �˴��ɽ���PD HRST��ش��� */
		
		
		
		
		PD_PHY_RX_INIT( );
	}
	
	/* ���ݰ���������ж� */
	if( PIF_TX_END ) 
    {		
		if( !( UPD_CTRL & bPD_CC_SEL ) ) 
        {
            CC1_CTRL &= ~bCC_LVO;	                                            /* ������ɹرյ�ѹ */
        }
		else 
        {
            CC2_CTRL &= ~bCC_LVO;
        }    
        
		if( PD_PHY_Stat.WaitingGCRC ) 
        {
			mTimer_x_SetData( 0, 4000 );		                                // 1ms @ 48MHz ��ȡGoodCRC�ĵ���ʱ
		}
		PD_PHY_RX_INIT( );
	}
	
	
	/* ���ݰ���������ж� */
	if( PIF_RX_ACT ) 
    {
		if( ( UPD_INT_FG & MASK_PD_STAT ) == PD_RX_SOP0 ) 
        {	
            /* �յ�SOP���� */
			
			if( PD_PHY_Stat.WaitingGCRC ) 
            {			
                /* ���ڵȴ�GoodCRC��Ϣ */
				Check_If_GoodCRC( );
			}
			else 
            {
				Set_TX_GoodCRC( );		                                        //�յ���Ϣ���ظ�GoodCRC
				PD_PROT_HANDLE( );
			}
		}
		PD_PHY_RX_INIT( );
	}
}

/********************************************************************************
* Function Name  : Timer0Interrupt
* Description    : ��ʱ���������ṩ1ms��ʱ���ɹ��û�������1msΪʱ��������
					��Э��ͨѶʱ����ʱ���ᱻ���ݵ��޸ģ���ʱ�����ᴥ���û���ʱ����
					��ȷʵ�ᵼ���û��Ķ�ʱ����ʱ����΢ƫ�ơ�
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/ 
void Timer0Interrupt( void ) interrupt INT_NO_TMR0                      
{  
	if( PD_PHY_Stat.QueueSendGCRC ) 
    {			
        /* �ظ�GoodCRC���� */
		PD_PHY_TX_INIT( PD_GCRC_BUF , 2 , PD_PHY_Stat.SOPType );
		PD_PHY_Stat.QueueSendGCRC = 0;
	}
	else if( PD_PHY_Stat.WaitingGCRC ) 
    {		
        /* ��ȡGoodCRC��ʱ */
		
		PD_PHY_Stat.RetryCnt --;
		if( PD_PHY_Stat.RetryCnt ) 
        {
			PD_PHY_TX_INIT( PD_TX_BUF , PD_PHY_Stat.MsgLen , PD_PHY_Stat.SOPType );
		}
		else 
        {
			PD_PHY_Stat.WaitingGCRC = 0;
			/* ��λ���� */
		}
	}
	else 
    {										
        /* Э��ƻ��������� */
		if( PD_PHY_Stat.MsgCnt ) 
        {
			PD_PHY_Stat.MsgCnt --;
			if( !PD_PHY_Stat.MsgCnt ) 
            {
				PD_PHY_Stat.RetryCnt = 3;
				PD_PHY_TX_INIT( PD_TX_BUF , PD_PHY_Stat.MsgLen , PD_PHY_Stat.SOPType );
				PD_PHY_Stat.WaitingGCRC = 1;
			}
		}
		
		/*  �˴����ͨ�ö�ʱ���� */
		
		
		
		
		/*  �˴����ͨ�ö�ʱ���� */
		
	}
	mTimer_x_SetData(0,4000);	               // 1ms @ 48MHz
}

/********************************************************************************
* Function Name  : Set_TX_GoodCRC
* Description    : ������ݺϷ��ԣ����ö�ʱ��Ϊ40us������GoodCRC����
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/ 
void Set_TX_GoodCRC( void )
{
	if( UPD_T_SOP ) 
    {
        return;
    }
    
	mTimer_x_SetData( 0, 200 );		                                            // 50us @ 48MHz
	
	Header = PD_RX_BUF;
	PD_PHY_Stat.RecvMsgID = Header->Struct.MsgID;		                        //����MsgID
	PD_PHY_Stat.QueueSendGCRC = 1;				                                //�÷���GoodCRC��־λ
	PD_PHY_Stat.SOPType = UPD_SOP0;
	
	Header = PD_GCRC_BUF;			                                            //����GoodCRC��Ϣ
	HeaderAutoFill( );
	Header->Struct.MsgID = PD_PHY_Stat.RecvMsgID;
}

/********************************************************************************
* Function Name  : Check_If_GoodCRC
* Description    : ����յ�����Ϣ�Ƿ�Ϊ�Ϸ�GoodCRC
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/ 
void Check_If_GoodCRC( void )
{
	Header = PD_RX_BUF;
	
	if( !( Header->Struct.MsgID ^ PD_PHY_Stat.SendMsgID ) && !( Header->Struct.MsgType ^ GoodCRC ) ) 
    {
		PD_PHY_Stat.SendMsgID++;
		PD_PHY_Stat.WaitingGCRC = 0;
	}
	
}

/********************************************************************************
* Function Name  : HeaderAutoFill
* Description    : ����ͳһ��ģ�������ϢHeader
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void HeaderAutoFill( void )
{
	Header->Struct.Extended = 0;
	Header->Struct.NDO = 0;
	Header->Struct.MsgID = PD_PHY_Stat.SendMsgID;
	Header->Struct.SpecRev = 1;
	Header->Struct.MsgType = GoodCRC;
	Header->Struct.DataRole = PD_PHY_Stat.PortDataRole;
	Header->Struct.PwrRole = PD_PHY_Stat.PortPwrRole;
	
}

/********************************************************************************
* Function Name  : PD_PHY_Init
* Description    : ��ʼ��PD PHY�Ͷ�ʱ��0
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void PD_PHY_Init( void )
{
	P1_MOD_OC &= ~( bCC1 | bCC2 );			//��ʼ��CC״̬
	P1_DIR_PU &= ~( bCC1 | bCC2 );
	CC1_CTRL = CC2_CTRL = bCC_CE | bCC_PD;
	
	PD_PHY_Stat.WaitingGCRC=0;				//��ʼ��PD���ñ���
	PD_PHY_Stat.QueueSendGCRC=0;	
	PD_PHY_Stat.RetryCnt=0;
	PD_PHY_Stat.SendMsgID=0;
	PD_PHY_Stat.RecvMsgID=0;
	PD_PHY_Stat.PortPwrRole=0;
	PD_PHY_Stat.PortDataRole=0;
	PD_PHY_Stat.ExpectPwrRole=1;
    PD_PHY_Stat.ExpectDataRole=1;
	PD_PHY_Stat.MsgCnt = 0;
	PD_PHY_Stat.tmp = 0x5A;
	
	mTimer0Clk12DivFsys( );					//TMR0 12��Ƶ
	mTimer_x_ModInit( 0, 1 );		      	//TMR0 16λ
	mTimer_x_SetData( 0, 4000 );	      	// 1ms @ 48MHz
	ET0 = 1;                              	//���ö�ʱ���ж�
	TR0 = 1;
}

/********************************************************************************
* Function Name  : PD_PHY_RX_INIT
* Description    : ��ʼ��PD PHY�Խ���һ����Ϣ
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void PD_PHY_RX_INIT( void )
{
	UPD_INT_EN = bPIE_RX_ACT | bPIE_RX_RST;
	
	UPD_CTRL |= ( bPD_CLR_ALL );
	UPD_CTRL &= ~( bPD_CLR_ALL | bPD_TX_EN );
	
	UPD_DMA_L = PD_RX_BUF;
	UPD_TIMER = FREQ_SYS/400000 - 1;
	PD_START = 1;
}

/********************************************************************************
* Function Name  : PD_PHY_TX_INIT
* Description    : ��ʼ��PD PHY�Է���һ����Ϣ
* Input          : PUINT8 Addr -> ������ϢDMA��ַ
*                  UINT8 Len -> ������Ϣ���ȣ�Byte��
*                  UINT8 sop -> ��Ϣ��SOP����
* Output         : None
* Return         : None
********************************************************************************/
void PD_PHY_TX_INIT( PUINT8 Addr, UINT8 Len, UINT8 sop )
{
	PD_START = 0;
	UPD_INT_EN = bPIE_TX_END;
	
	UPD_T_SOP = sop;
	UPD_T_LEN = Len;
	
	UPD_CTRL |= ( bPD_CLR_ALL | bPD_TX_EN );
	UPD_CTRL &= ~( bPD_CLR_ALL );
	
	UPD_DMA_L = Addr;
	UPD_TIMER = FREQ_SYS/600000 - 1;
	
	if( !( UPD_CTRL & bPD_CC_SEL ) ) 
    {
        CC1_CTRL |= bCC_LVO;	                   //����ʱ�õ�ѹ
    }    
	else 
    {
        CC2_CTRL |= bCC_LVO;
    }
	PD_START = 1;
}
