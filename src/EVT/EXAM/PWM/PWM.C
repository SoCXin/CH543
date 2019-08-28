/********************************** (C) COPYRIGHT *******************************
* File Name          : PWM.C
* Author             : WCH
* Version            : V1.0
* Date               : 2022/01/13
* Description        : CH543 PWM�������ѡ���жϴ���(PWM ѭ�����ڽ����ж�)
*                      ����           ����
*                      P15            PWM0
*                      P34            PWM1
*                      P16            PWM2
*                      P14            PWM3
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/



/*******************************************************************************/
/* ͷ�ļ����� */
#include ".\PWM\PWM.H"
#pragma  NOAREGS

/********************************************************************************
* Function Name  : PWM_SEL_CHANNEL( UINT8 Channel,UINT8 NewState )
* Description    : PWMͨ�����ʹ��,����IO�˿�����
* Input          : Channel��ͨ����,λ���ʾ
*                  NewState��0:�ر�ͨ��  1:����ͨ��
* Output         : None
* Return         : None
********************************************************************************/
void PWM_SEL_CHANNEL( UINT8 Channel, UINT8 NewState )
{
    UINT8 i;
	
    /* ͨ������ */
    if( NewState == Enable )													/* ������� */
    {
        PWM_CTRL &= ~bPWM_CLR_ALL;
        
		if( Channel & CH0 )
        {
            PWM_CTRL |= bPWM0_OUT_EN;
            P1_MOD_OC &= ~( 1 << 5 );             								/* ��Ӧ��GPIO�����ó�����ģʽ */
            P1_DIR_PU |= ( 1 << 5 );
        }
		
        if( Channel & CH1 )
        {
            PWM_CTRL |= bPWM1_OUT_EN;
            P3_MOD_OC &= ~( 1 << 4 );
            P3_DIR_PU |= ( 1 << 4 );
        }
		
        if( Channel & CH2 )
        {
            PWM_CTRL2 |= bPWM2_OUT_EN;
            P1_MOD_OC &= ~( 1 << 6 );
            P1_DIR_PU |= ( 1 << 6 );
        }
		
        if( Channel & CH3 )
        {
            PWM_CTRL2 |= bPWM3_OUT_EN;
            P1_MOD_OC &= ~( 1 << 4 );
            P1_DIR_PU |= ( 1 << 4 );
        }
    }
    else                                      									/* ����ر� */
    {
        if( Channel & CH0 )
        {
            PWM_CTRL &= ~bPWM0_OUT_EN;
        }
		
        if(Channel & CH1 )
        {
            PWM_CTRL &= ~bPWM1_OUT_EN;
        }
		
        if( Channel & CH2 )
        {
            PWM_CTRL2 &= ~bPWM2_OUT_EN;
        }
		
        if( Channel & CH3 )
        {
            PWM_CTRL2 &= ~bPWM3_OUT_EN;
        }
    }
}

#ifdef PWM_INTERRUPT
/********************************************************************************
* Function Name  : PWMInterruptEnable( void )
* Description    : PWM�ж�ʹ��
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void PWMInterruptEnable( void )
{
    PWM_CTRL |= bPWM_IE_END;
    PWM_CTRL |= bPWM_IF_END;													/* ���PWM�ж� */
    IE_PWMX = 1;
    EA = 1;
}

/********************************************************************************
* Function Name  : PWMInterrupt( void )
* Description    : PWM0~3�жϷ������,ʹ�üĴ�����1
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void PWMInterrupt( void ) interrupt INT_NO_PWMX using 1                       	
{
    static UINT8 duty = 0;
	
    PWM_CTRL |= bPWM_IF_END;                                                  	/* ���PWM�ж� */

    /* ��ѡ��,��������ռ�ձ� */
    SetPWM0Dat( duty );
    SetPWM1Dat( duty );
    SetPWM2Dat( duty );
    SetPWM3Dat( duty );
    duty += 3;
}
#endif