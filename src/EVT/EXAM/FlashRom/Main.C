/********************************** (C) COPYRIGHT ********************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 FlashRom操作演示示例
                       1、DataFlash读写操作
                       2、CodeFlash读写操作
                       3、配置信息读取
                       4、设备唯一ID读取
                       5、OTP区读写
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/


/*******************************************************************************/
/* 头文件包含 */	
#include ".\Public\CH543.H"
#include ".\Public\DEBUG.H"
#include ".\FlashRom\FlashRom.H"
#pragma  NOAREGS

/*******************************************************************************/
/* 常、变量定义 */
UINT8X FlashBuf[ 64 ] _at_ 0x0000;                                                /* 对应于Flash页写的一个页,需要64字节对齐 */
UINT8X temp[ 64 ];

/*******************************************************************************
* Function Name  : main
* Description    : 主程序
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void main()
{
    
    UINT8 s, i, len;
    
    /*****************************系统相关初始化********************************/
    CfgFsys( );                                                                 /* CH543时钟选择配置 */
    mDelaymS( 20 );
    mInitSTDIO( );                                                              /* 串口0初始化 */
    
    printf("FlashRom demo start ...\n");
    for( i = 0; i != 64; i++ )
    {
        FlashBuf[ i ] = i;
    }
    
    /* 1、DataFlash 操作演示 */
    memset( temp, 0, 64 );
    printf("DataFlash Erase...\n");
    s = FlashErasePage( 0x3800 ) ;                                              /* 擦除DataFlash的第一页 */
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
    
    /* 2、Code Flash 操作演示(BOOT区域用户程序无读写权限) */
    memset( temp, 0, 64 );
    printf("CodeFlash Erase...\n");
    s = FlashErasePage( 0x37C0 ) ;                                              /* 擦除CodeFlash 0x37C0所在页 */
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
    
    /* 3、16字节配置位读取 */
    printf("Config Information Read...\n");
    len = FlashReadBuf( 0x3FFE, temp, 2 );
    printf("real len:%d\n",(UINT16)len);
    printf("cfg:%02x %02x\n",(UINT16)temp[1],(UINT16)temp[0]);
    
    /* 4、读取设备唯一ID（只读区地址 10H~15H） 16h~17H是校验和 */
    printf("Unique ID...\n");
    printf("0x%lx " ,FlashReadOTPword( 0x14 ));                                 /* 17H,16H,15H,14H */
    printf("0x%lx\n",FlashReadOTPword( 0x10 ));                                 /* 13H,12H,11H,10H */
    
#if 0
    /* 5、OTP 操作(只能0变成1,且不可擦除) */
    printf("OTP Read:");
    printf("0x%lx \n",FlashReadOTPword( 0x20 ));                                /* 读取0x20开始的四字节 */
    printf("OTP Write ...\n");
    s = FlashProgOTPbyte( 0x20, 0x4f );                                         /* 从0x20地址开始写入 */
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
    printf("0x%lx \n",FlashReadOTPword( 0x20 ));                                /* 再次读取0x20开始的四字节 */
#endif
    
    /*****************************主循环***************************************/
    while( 1 );
}
