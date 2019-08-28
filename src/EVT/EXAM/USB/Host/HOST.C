/********************************** (C) COPYRIGHT *******************************
* File Name          : Host.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : USB����Ӧ������ ��ʵ�ּ��̡���ꡢU��ö�١�HID����
                       ע������ļ�USBHOST.C/DEBUG.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\USB\USB_LIB\USBHOST.H"

/********************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void main( void )
{
	UINT8  i, s, len, endp;
	UINT16 loc;
	
	CfgFsys( );																	/* CH543ʱ��ѡ������ */
	mInitSTDIO();  																/* Ϊ���ü����ͨ�����ڼ����ʾ���� */
	printf("Start @ChipID=%02X\n", (UINT16)CHIP_ID);
	InitUSB_Host( );

	FoundNewDev = 0;
	printf("Wait Device In\n");
	
    while( 1 )
	{			
        s = ERR_SUCCESS;
		
		if( UIF_DETECT )														/* �����USB��������ж����� */
		{  																					
			UIF_DETECT = 0;  													/* ���жϱ�־ */
			s = AnalyzeRootHub( );   											/* ����ROOT-HUB״̬ */
			
			if( s == ERR_USB_CONNECT ) FoundNewDev = 1;
		}
		
		if( FoundNewDev || s == ERR_USB_CONNECT )								/* ���µ�USB�豸���� */	
		{  			
			FoundNewDev = 0;
			mDelaymS( 200 );  													/* ����USB�豸�ղ�����δ�ȶ�,�ʵȴ�USB�豸���ٺ���,������ζ��� */		
			s = EnumAllRootDevice();  											/* ö������ROOT-HUB�˿ڵ�USB�豸 */
			
			if( s != ERR_SUCCESS ) printf("EnumAllRootDev err = %02X\n",(UINT16)s);
		}
		
		mDelaymS( 100 );  														/* ģ�ⵥƬ���������� */	
        loc = SearchTypeDevice( DEV_TYPE_MOUSE );  								/* ��ROOT-HUB�Լ��ⲿHUB���˿�������ָ�����͵��豸���ڵĶ˿ں� */	
		
		if( loc != 0xFFFF )														/* �ҵ���,���������MOUSE��δ���? */	
		{  															
			i = (UINT8)( loc >> 8 );
			len = (UINT8)loc;
			SelectHubPort( len );  												/* ѡ�����ָ����ROOT-HUB�˿�,���õ�ǰUSB�ٶ��Լ��������豸��USB��ַ */	
			
			/* �ж϶˵�ĵ�ַ,λ7����ͬ����־λ */
			endp = len ? DevOnHubPort[ len - 1 ].GpVar[ 0 ] : ThisUsbDev.GpVar[ 0 ];	
			
			if( endp & USB_ENDP_ADDR_MASK )										/* �˵���Ч */
			{  
				/* CH543��������,��ȡ����,NAK������ */
				s = USBHostTransact( USB_PID_IN << 4 | endp & 0x7F, endp & 0x80 ? bUH_R_TOG | bUH_T_TOG : 0, 0 );  
				
				if( s == ERR_SUCCESS ) 
				{
					endp ^= 0x80;  												/* ͬ����־��ת */
					
					if( len ) DevOnHubPort[ len - 1 ].GpVar[ 0 ] = endp; 		/* ����ͬ����־λ */
					else ThisUsbDev.GpVar[ 0 ] = endp;
					
					len = USB_RX_LEN;  											/* ���յ������ݳ��� */
					
					if( len )
					{
						printf("Mouse data: ");
						for( i = 0; i < len; i++ ) printf("x%02X ",(UINT16)(RxBuffer[ i ]));
						printf("\n");
					}
				}
				else if( s != ( USB_PID_NAK | ERR_USB_TRANSFER ) ) printf("Mouse error %02x\n",(UINT16)s);  /* �����ǶϿ��� */
			}
			else printf("Mouse no interrupt endpoint\n");
			SetUsbSpeed( 0 );  													/* Ĭ��Ϊ���� */
		}
    }
}







