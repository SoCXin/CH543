/********************************** (C) COPYRIGHT *******************************
* File Name          : CompatibilityHID.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543ģ��HID�����豸,֧���ж����´�,֧�ֿ��ƶ˵����´�,֧��ȫ�ٴ���
                       ע�����DEBUG.C
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */
#include ".\Public\DEBUG.H"

/******************************************************************************/
/* ������������ */
#define THIS_ENDP0_SIZE         64
#define ENDP2_IN_SIZE           64
#define ENDP2_OUT_SIZE          64
#pragma NOAREGS

/* �˵�0 OUT&IN������,������ż��ַ */
UINT8X  Ep0Buffer[ MIN( 64, THIS_ENDP0_SIZE + 2 ) ] _at_ 0x0000;
/* �˵�2 IN&OUT������,������ż��ַ */
UINT8X  Ep2Buffer[ MIN( 64,ENDP2_IN_SIZE + 2 ) + MIN( 64, ENDP2_OUT_SIZE + 2 ) ] _at_ MIN( 64, THIS_ENDP0_SIZE + 2 );

UINT8   Ready, UsbConfig;
UINT8X  UserEp2Buf[ 64 ];                                                       /* �û����ݶ��� */
UINT8   Endp2Busy = 0;

#define UsbSetupBuf     ( (PUSB_SETUP_REQ)Ep0Buffer )
sbit Ep2InKey = P1^5;                                                           /* K1���� */

/******************************************************************************/
/* USB�豸������ */
UINT8C DevDesc[ ] = 
{
    0x12, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, THIS_ENDP0_SIZE,
    0x86, 0x1A, 0x10, 0xE0, 0x00, 0x00, 0x01, 0x02,
    0x00, 0x01
};

/******************************************************************************/
/*HID�౨��������*/
UINT8C HIDRepDesc[ ] =
{
    0x06, 0xA0, 0xff,
    0x09, 0x01,
    0xa1, 0x01,                                                                 /* ���Ͽ�ʼ */
    0x09, 0x01,                                                                 /* Usage Page  �÷� */
    0x15, 0x00,                                                                 /* Logical  Minimun */
    0x26, 0x00, 0xff,                                                           /* Logical  Maximun */
    0x75, 0x08,                                                                 /* Report Size */
    0x95, THIS_ENDP0_SIZE,                                                      /* Report Counet */
    0x81, 0x02,                                                                 /* Input */
    0x09, 0x02,                                                                 /* Usage Page  �÷� */
    0x75, 0x08,                                                                 /* Report Size */
    0x95, THIS_ENDP0_SIZE,                                                      /* Report Counet */
    0x91, 0x02,                                                                 /* Output */
    0x09, 0x03,
    0x75, 0x08,
    0x95, THIS_ENDP0_SIZE,
    0xB1, 0x02,
    0xC0
};

/******************************************************************************/
/* USB���������� */
UINT8C CfgDesc[ ] =
{
    0x09, 0x02, 0x29, 0x00, 0x01, 0x01, 0x04, 0xA0, 0x23,                       /* ���������� */
    0x09, 0x04, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00,                       /* �ӿ������� */
    0x09, 0x21, 0x00, 0x01, 0x00, 0x01, 0x22, sizeof( HIDRepDesc ) & 0xFF, sizeof( HIDRepDesc ) >> 8,     /* HID�������� */
    0x07, 0x05, 0x82, 0x03, ENDP2_IN_SIZE, 0x00, 0x01,                          /* �˵������� */
    0x07, 0x05, 0x02, 0x03, ENDP2_OUT_SIZE, 0x00, 0x01,                         /* �˵������� */
};

/*****************************************************************************************/
/* �����ַ��������� */
UINT8C  MyLangDescr[ ] = { 0x04, 0x03, 0x09, 0x04 };

/*****************************************************************************************/
/* �����ַ��������� */
UINT8C  MyManuInfo[ ] = { 0x0E, 0x03, 'w', 0, 'c', 0, 'h', 0, '.', 0, 'c', 0, 'n', 0 };

/*****************************************************************************************/
/* ��Ʒ�ַ��������� */
UINT8C  MyProdInfo[ ] = { 0x0C, 0x03, 'C', 0, 'H', 0, '5', 0, '4', 0, '3', 0 };

/*******************************************************************************
* Function Name  : USB_DeviceInterrupt
* Description    : USB�жϷ������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_DeviceInterrupt( void ) interrupt INT_NO_USB using 1	
{
	UINT8	i;
	UINT16 len;
	static	UINT8	SetupReqCode;
    static	UINT16	SetupLen;
	static	PUINT8	pDescr;

	if( UIF_TRANSFER )                                                          /* USB������� */
    {
USB_DevIntNext:      
		switch( USB_INT_ST & ( bUIS_SETUP_ACT | MASK_UIS_TOKEN | MASK_UIS_ENDP ) )  /* �����������ƺͶ˵�� */
        {
			case UIS_TOKEN_OUT | 2:                                             /* endpoint 2# �����˵��´� */
			case bUIS_SETUP_ACT | UIS_TOKEN_OUT | 2:
				if(U_TOG_OK)                                                    /* ��ͬ�������ݰ������� */
                { 
					UEP2_CTRL ^= bUEP_R_TOG;                                    /* �ֶ���ת */
					len = USB_RX_LEN;
					for( i = 0; i < len; i ++ )
                    {
						Ep2Buffer[ MAX_PACKET_SIZE + i ] = Ep2Buffer[ i ] ^ 0xFF;   /* OUT����ȡ����IN�ɼ������֤ */
					}
					UEP2_T_LEN = len;
					UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;   /* �����ϴ� */
				}
				break;
			case UIS_TOKEN_IN | 2:                                              /* endpoint 2# �����˵��ϴ� */
			case bUIS_SETUP_ACT | UIS_TOKEN_IN | 2:
					UEP2_T_LEN = 0;                                             /* Ԥʹ�÷��ͳ���һ��Ҫ��� */
					UEP2_CTRL ^= bUEP_T_TOG;                                    /* �ֶ���ת */
					Endp2Busy = 0;
					UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;   /* Ĭ��Ӧ��NAK */
				break;
			case UIS_TOKEN_IN | 0:                                              /* endpoint 0# IN */
			case bUIS_SETUP_ACT | UIS_TOKEN_IN | 0:
				switch( SetupReqCode )
                {
					case USB_GET_DESCRIPTOR:
					case HID_GET_REPORT:
						len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen;  /* ���δ��䳤�� */
						memcpy( Ep0Buffer, pDescr, len );                       /* �����ϴ����� */
						SetupLen -= len;
						pDescr += len;
						UEP0_T_LEN = len;
						UEP0_CTRL ^= bUEP_T_TOG;                                /* ��ת */
						break;
					case USB_SET_ADDRESS:
						USB_DEV_AD = USB_DEV_AD & bUDA_GP_BIT | SetupLen;
						UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
						break;
					default:
                        /* ״̬�׶�����жϻ�����ǿ���ϴ�0�������ݰ��������ƴ��� */
						UEP0_T_LEN = 0; 
						UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
						break;
				}
				break;
			case UIS_TOKEN_OUT | 0:                                             /* endpoint 0# OUT */
			case bUIS_SETUP_ACT | UIS_TOKEN_OUT | 0:
				len = USB_RX_LEN;
				UEP0_CTRL ^= bUEP_R_TOG;                                        /* ͬ����־λ��ת */
				break;
			default:
				if( ( USB_INT_ST & ( bUIS_SETUP_ACT | MASK_UIS_TOKEN ) ) == ( bUIS_SETUP_ACT | UIS_TOKEN_FREE ) )  /* endpoint 0# SETUP */
                {
					UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK; 
					SetupLen = ( (UINT16)UsbSetupBuf->wLengthH << 8 ) + UsbSetupBuf->wLengthL;    /* Ĭ��Ϊ�ɹ������ϴ�0���� */
					SetupReqCode = UsbSetupBuf->bRequest;
					len = 0;                                                    /* Ĭ��Ϊ�ɹ������ϴ�0���� */
					if( ( UsbSetupBuf->bRequestType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )
                    {  
						switch( SetupReqCode )
                        {							 
							case 0x01:                                          /* GetReport */
								pDescr = UserEp2Buf;                            /* ���ƶ˵��ϴ���� */
								if(SetupLen >= THIS_ENDP0_SIZE)                 /* ���ڶ˵�0��С����Ҫ���⴦�� */
								{
									len = THIS_ENDP0_SIZE;
								}
								else
								{
									len = SetupLen;
								}
								break;
							case 0x02:                                          /* GetIdle */
								break;
							case 0x03:                                          /* GetProtocol */
								break;
							case 0x09:                                          /* SetReport */
								break;
							case 0x0A:                                          /* SetIdle */
								break;
							case 0x0B:                                          /* SetProtocol */
								break;
							default:
								len = 0xFFFF;                                   /* ���֧�� */
								break;
						}
						if(SetupLen > len)
						{
							SetupLen = len;                                     /* �����ܳ��� */
						}
						len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen;     /* ���δ��䳤�� */
						memcpy( Ep0Buffer, pDescr, len );                                   /* �����ϴ����� */
						SetupLen -= len;
						pDescr += len;
					}
					else                                                        /* ��׼����	*/
                    {					
						switch( SetupReqCode )                                  /* ������ */
                        {
							case USB_GET_DESCRIPTOR:
								switch( UsbSetupBuf->wValueH )
                                {
									case 1:                                     /* �豸������ */
										pDescr = (PUINT8)( &DevDesc[ 0 ] );
										len = sizeof( DevDesc );
										break;
									case 2:                                     /* ���������� */
										pDescr = (PUINT8)( &CfgDesc[ 0 ] );
										len = sizeof( CfgDesc );
										break;
									case 3:                                     /* �ַ��������� */
										switch( UsbSetupBuf->wValueL )
                                        {
											case 1:
												pDescr = (PUINT8)( &MyManuInfo[ 0 ] );
												len = sizeof( MyManuInfo );
												break;
											case 2:
												pDescr = (PUINT8)( &MyProdInfo[ 0 ] );
												len = sizeof( MyProdInfo );
												break;
											case 0:
												pDescr = (PUINT8)( &MyLangDescr[ 0 ] );
												len = sizeof( MyLangDescr );
												break;
											default:
												len = 0xFFFF;                   /* ��֧�ֵ��ַ��������� */
												break;
										}
										break;
									case 0x22:                                  /* ���������� */
										pDescr = HIDRepDesc;                    /* ����׼���ϴ� */
										len = sizeof( HIDRepDesc );
									break;
									default:
										len = 0xFFFF;                           /* ��֧�ֵ����������� */
										break;
								}
								if( SetupLen > len ) SetupLen = len;            /* �����ܳ��� */
								len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen;     /* ���δ��䳤�� */
								memcpy( Ep0Buffer, pDescr, len );               /* �����ϴ����� */
								SetupLen -= len;
								pDescr += len;
								break;
							case USB_SET_ADDRESS:
								SetupLen = UsbSetupBuf->wValueL;                /* �ݴ�USB�豸��ַ */
								break;
							case USB_GET_CONFIGURATION:
								Ep0Buffer[ 0 ] = UsbConfig;
								if( SetupLen >= 1 ) len = 1;
								break;
							case USB_SET_CONFIGURATION:
								UsbConfig = UsbSetupBuf->wValueL;
								if( UsbConfig ) Ready = 1;									
								break;
							case USB_CLEAR_FEATURE:
								if( ( UsbSetupBuf->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )      /* �˵� */
                                { 
									switch( UsbSetupBuf->wIndexL )
                                    {
										case 0x82:
											UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
											break;
										case 0x02:
											UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
											break;
										case 0x81:
											UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
											break;
										case 0x01:
											UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
											break;
										default:
											len = 0xFFFF;                       /* ��֧�ֵĶ˵� */
											break;
									}
								}
								else len = 0xFFFF;                              /* ���Ƕ˵㲻֧�� */
								break;
							case USB_SET_FEATURE:                               /* Set Feature */
								if( ( UsbSetupBuf->bRequestType & 0x1F ) == 0x00)       /* �����豸 */
								{
									if( ( ( (UINT16)UsbSetupBuf->wValueH << 8 ) | UsbSetupBuf->wValueL ) == 0x01)
									{
										if( CfgDesc[ 7 ] & 0x20 )
										{
                                                                                /* ���û���ʹ�ܱ�־ */
										}
										else
										{
											len = 0xFFFF;                       /* ����ʧ�� */
										}
									}
									else
									{
										len = 0xFFFF;                           /* ����ʧ�� */
									}
								}
								else if( ( UsbSetupBuf->bRequestType & 0x1F ) == 0x02 )   /* ���ö˵� */
								{
									if( ( ( (UINT16)UsbSetupBuf->wValueH << 8) | UsbSetupBuf->wValueL) == 0x00 )
									{
										switch( ( (UINT16)UsbSetupBuf->wIndexH << 8) | UsbSetupBuf->wIndexL )
                                        {
											case 0x82:
												UEP2_CTRL = UEP2_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;    /* ���ö˵�2 IN STALL */
												break;
											case 0x02:
												UEP2_CTRL = UEP2_CTRL & (~bUEP_R_TOG) | UEP_R_RES_STALL;    /* ���ö˵�2 OUT STALL */
												break;
											case 0x81:
												UEP1_CTRL = UEP1_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;    /* ���ö˵�1 IN STALL */
												break;
											default:
												len = 0xFFFF;                   /* ����ʧ�� */
												break;
										}
									}
									else
									{
										len = 0xFFFF;                           /* ����ʧ�� */
									}
								}
								else
								{
									len = 0xFFFF;                               /* ����ʧ�� */
								}
								break;
							case USB_GET_INTERFACE:
								Ep0Buffer[ 0 ] = 0x00;
								if( SetupLen >= 1 ) len = 1;
								break;
							case USB_GET_STATUS:
								Ep0Buffer[ 0 ] = 0x00;
								Ep0Buffer[ 1 ] = 0x00;
								if( SetupLen >= 2 ) len = 2;
								else len = SetupLen;
								break;
							default:
								len = 0xFFFF;                                   /* ����ʧ�� */
								printf("ErrEp0ReqCode=%02X\n",(UINT16)SetupReqCode);
								break;
						}
					}
					if( len == 0xFFFF )                                         /* ����ʧ�� */
                    {
						SetupReqCode = 0xFF;
						UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;    /* STALL */
					}
					else if(len <= THIS_ENDP0_SIZE)                             /* �ϴ����ݻ���״̬�׶η���0���Ȱ� */
                    {
						UEP0_T_LEN = len;
						UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;        /* Ĭ�����ݰ���DATA1 */
					}
					else                                                        /* �´����ݻ����� */
                    {
                        /* ��Ȼ��δ��״̬�׶Σ�������ǰԤ���ϴ�0�������ݰ��Է�������ǰ����״̬�׶� */
						UEP0_T_LEN = 0;
						UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;        /* Ĭ�����ݰ���DATA1 */
					}
					break;
				}
				else {
					printf("ErrEndpInt\n");
					break;
				}
		}
		UIF_TRANSFER = 0;                                                       /* ���жϱ�־ */
	}
	else if( UIF_BUS_RST )                                                      /* USB���߸�λ */
    {
		printf("rst\n");                                                        /*  ˯��״̬ */
		UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
		UEP2_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
		USB_DEV_AD = 0x00;
		UIF_SUSPEND = 0;
		UIF_TRANSFER = 0;
		Endp2Busy = 0;
		Ready = 0;
		UIF_BUS_RST = 0;                                                        /* ���жϱ�־ */
	}
	else if( UIF_SUSPEND )                                                      /* USB���߹���/������� */
    {
		UIF_SUSPEND = 0;
		if(USB_MIS_ST & bUMS_SUSPEND)                                           /* ���� */
        {
			printf("sleep\n");                                                  /* ˯��״̬ */
		}
		else{                                                                   /* ���� */
            printf("weak\n");                                                   /* ˯��״̬ */
			
		}
	}
	else                                                                        /* ������ж�,�����ܷ�������� */
    {
		printf("UnknownERR\n");
		USB_INT_FG = 0xFF;                                                      /* ���жϱ�־ */
	}
	if( UIF_TRANSFER ) goto USB_DevIntNext;
	
}

/*******************************************************************************
* Function Name  : Enp2BlukIn
* Description    : USB�豸ģʽ�˵�2�������ϴ�
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Enp2BlukIn( UINT8 *buf, UINT8 len)
{
    memcpy( Ep2Buffer + MAX_PACKET_SIZE, buf, len);                             /* �����ϴ����� */
    UEP2_T_LEN = len;                                                           /* �ϴ��������� */
    UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;                   /* ������ʱ�ϴ����ݲ�Ӧ��ACK */
}

/*******************************************************************************
* Function Name  : InitUSB_Device
* Description    : ��ʼ��USB�豸
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*--------------------------------------------------------------
          | bUDP_PUE | bUDM_PUE | bUD_LOW_SPEED | bUC_LOW_SPEED
Low  Speed|    0     |    1     |       1       |       1        
Full Speed|    1     |    0     |       0       |       0
---------------------------------------------------------------*/
void InitUSB_Device( void )  
{
	IE_USB = 0;
	
	USB_CTRL = 0x00;                                                            /* ���趨ģʽ */
	UEP2_3_MOD |= bUEP2_RX_EN | bUEP2_TX_EN;                                    /* �˵�2�´�OUT���ϴ�IN */
	UEP2_T_LEN = 0;                                                             /* Ԥʹ�÷��ͳ���һ��Ҫ��� */
	UEP0_DMA_L = Ep0Buffer;
	UEP2_DMA_L = Ep2Buffer;
	USB_DEV_AD = 0x00;
	USB_PULL = 0x00;                                                            /* ��ֹDP/DM�������� */
	UDEV_CTRL &= ~bUD_LOW_SPEED;                                                /* ѡ��ȫ��12Mģʽ��Ĭ�Ϸ�ʽ */
	USB_CTRL &= ~bUC_LOW_SPEED;
    USB_PULL = bUDP_PUE;                                                        /* Full Speed */
	USB_CTRL |= bUC_DEV_EN | bUC_INT_BUSY;                                      /* ����USB�豸��DMA�����ж��ڼ��жϱ�־δ���ǰ�Զ�����NAK */
	UDEV_CTRL |= bUD_PORT_EN;                                                   /* ����USB�˿� */
	USB_INT_FG = 0xFF;                                                          /* ���жϱ�־ */
	USB_INT_EN = bUIE_SUSPEND | bUIE_TRANSFER | bUIE_BUS_RST;
	IE_USB = 1;
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None	
* Return         : None
*******************************************************************************/
void main(void)
{
	UINT8 i;
    
    /*****************************ϵͳ��س�ʼ��*******************************/
	CfgFsys( );                                                                 /* CH543ʱ��ѡ������ */
	mDelaymS( 20 );                                                             /* �޸���Ƶ�ȴ��ڲ������ȶ�,�ؼ� */
	mInitSTDIO( );                                                              /* ����0��ʼ�� */
	printf("start ...\n");

	for( i=0; i<64; i++ )                                                       /* ׼����ʾ���� */
	{
		UserEp2Buf[ i ] = i;
	}
    /* USB�豸��ʼ�� */ 
	InitUSB_Device( );                                                          /* USB�豸ģʽ��ʼ�� */
	EA = 1;                                                                     /* ������Ƭ���ж� */
	
    /*****************************��ѭ��**************************************/	
	while(1)
	{
		if( ( Ep2InKey == 0 ) )
		{				
			while( Endp2Busy )
			{				
                ;                                                               /* ���æ����һ������û�д���ȥ��,��ȴ��� */
			}
			Endp2Busy = 1;                                                      /* ����Ϊæ״̬ */
			Enp2BlukIn( UserEp2Buf, THIS_ENDP0_SIZE );
		}
		mDelaymS( 100 );                                                        /* ģ�ⵥƬ���������� */
	}
}