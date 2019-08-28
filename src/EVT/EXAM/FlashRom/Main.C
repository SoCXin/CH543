/********************************** (C) COPYRIGHT ********************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 FlashRom������ʾʾ��
                       1��DataFlash��д����
                       2��CodeFlash��д����
                       3��������Ϣ��ȡ
                       4���豸ΨһID��ȡ
                       5��OTP����д
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


/*******************************************************************************/
/* ͷ�ļ����� */	
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\FlashRom\FlashRom.H"
#pragma  NOAREGS

/*******************************************************************************/
/* ������������ */
UINT8X FlashBuf[ 64 ] _at_ 0x0000;                                                /* ��Ӧ��Flashҳд��һ��ҳ,��Ҫ64�ֽڶ��� */
UINT8X temp[ 64 ];

/*******************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void main()
{
    
    UINT8 s, i, len;
    
    /*****************************ϵͳ��س�ʼ��********************************/
    CfgFsys( );                                                                 /* CH543ʱ��ѡ������ */
    mDelaymS( 20 );
    mInitSTDIO( );                                                              /* ����0��ʼ�� */
    
    printf("FlashRom demo start ...\n");
    for( i = 0; i != 64; i++ )
    {
        FlashBuf[ i ] = i;
    }
    
    /* 1��DataFlash ������ʾ */
    memset( temp, 0, 64 );
    printf("DataFlash Erase...\n");
    s = FlashErasePage( 0x3800 ) ;                                              /* ����DataFlash�ĵ�һҳ */
    if( s != 0x00 )
    {
        printf("%02x \n",(UINT16)s);
    }
    printf("DataFlash Write...\n");
    s = FlashProgPage( 0x3800, FlashBuf, 64 );
    if(s != 0x00)
    {
        printf( "%02x \n",(UINT16)s );
    }
    printf("DataFlash Read...\n");
    len = FlashReadBuf( 0x3800, temp, 64 );
    printf("real len:%d\n",(UINT16)len);
    for( i = 0; i != len; i++ )
    {
        printf("%02x ",(UINT16)temp[ i ]);
        if(temp[ i ]!=FlashBuf[ i ])
        {
            printf("Err Offset:%02x\n",i);
            while( 1 )
            {
                ;
            }
        }
    }
    printf("\n\n");
    
    /* 2��Code Flash ������ʾ(BOOT�����û������޶�дȨ��) */
    memset( temp, 0, 64 );
    printf("CodeFlash Erase...\n");
    s = FlashErasePage( 0x37C0 ) ;                                              /* ����CodeFlash 0x37C0����ҳ */
    if( s != 0x00 )
    {
        printf("%02x \n",(UINT16)s);
    }
    printf("CodeFlash Write...\n");
    s = FlashProgPage( 0x37C0, &FlashBuf[ 0 ], 64 );
    if(s != 0x00)
    {
        printf("%02x \n",(UINT16)s);
    }
    printf("CodeFlash Read...\n");
    len = FlashReadBuf( 0x37C0, temp, 64 );
    printf("real len:%d\n",(UINT16)len);
    for( i = 0; i != len; i++ )
    {
        printf("%02x ",(UINT16)temp[ i ]);
        if( temp[ i ] != FlashBuf[ i ])
        {
            printf("Err Offset:%02x\n",i);
            while( 1 )
            {
                ;
            }
        }
    }
    printf("\n\n");
    
    /* 3��16�ֽ�����λ��ȡ */
    printf("Config Information Read...\n");
    len = FlashReadBuf( 0x3FFE, temp, 2 );
    printf("real len:%d\n",(UINT16)len);
    printf("cfg:%02x %02x\n",(UINT16)temp[1],(UINT16)temp[0]);
    
    /* 4����ȡ�豸ΨһID��ֻ������ַ 10H~15H�� 16h~17H��У��� */
    printf("Unique ID...\n");
    printf("0x%lx " ,FlashReadOTPword( 0x14 ));                                 /* 17H,16H,15H,14H */
    printf("0x%lx\n",FlashReadOTPword( 0x10 ));                                 /* 13H,12H,11H,10H */
    
#if 0
    /* 5��OTP ����(ֻ��0���1,�Ҳ��ɲ���) */
    printf("OTP Read:");
    printf("0x%lx \n",FlashReadOTPword( 0x20 ));                                /* ��ȡ0x20��ʼ�����ֽ� */
    printf("OTP Write ...\n");
    s = FlashProgOTPbyte( 0x20, 0x4f );                                         /* ��0x20��ַ��ʼд�� */
    if(s != 0x00)
    {
        printf("s = %02x \n",(UINT16)s);
    }
    s = FlashProgOTPbyte( 0x21, 0x58 );
    if(s != 0x00)
    {
        printf("s = %02x \n",(UINT16)s);
    }
    s = FlashProgOTPbyte( 0x22, 0x54 );
    if(s != 0x00)
    {
        printf("s = %02x \n",(UINT16)s);
    }
    s = FlashProgOTPbyte( 0x23, 0x63 );
    if(s != 0x00)
    {
        printf("s = %02x \n",(UINT16)s);
    }
    printf("OTP Read:");
    printf("0x%lx \n",FlashReadOTPword( 0x20 ));                                /* �ٴζ�ȡ0x20��ʼ�����ֽ� */
#endif
    
    /*****************************��ѭ��***************************************/
    while( 1 );
}