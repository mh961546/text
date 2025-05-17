/*
 * menu.h
 *  Created on: Feb 8, 2024
 *      Author: HXP119
 */

#ifndef __MENU_H
#define __MENU_H
#include "stm32g4xx_hal.h" //HAL���ļ�����
#include "main.h" //IO�������ʼ��������main.c�ļ��У���������
#include "adc.h"
#include "tim.h"
#include "opamp.h"

#include "MENU.h"
#include "KEY.h"
#include "OLED.h"
#include "ownfliter.h"
#include "BDA_Control.h"
#include "ControlLoop.h"
typedef enum {
    STATE_IDLE,       // ����״̬
    STATE_OFF_GRID,   // �������-��ѹԴģʽ
    STATE_F_ACVSET,     // �������ģʽ�������ѹ

    STATE_ON_GRID,    // �������-����Դģʽ
	STATE_O_CURSET,     // �������ģʽ��������
    STATE_O_K_SET,     // �������ģʽKֵ����

     STATE_BDIV,       // ˫�����������ֱ�����ѹ
    
} SystemState;

extern volatile SystemState menu_current_state; // ����ȫ��״̬����

/****��Ҫ�����ı���****/
extern float AC_current_target;		//����������Ŀ���趨ֵ
extern float AC_voltage_target;		//�������ѹ��Ŀ���趨ֵ
extern float DC_voltage_target;		//ֱ�����ѹ��Ŀ���趨ֵ

/****��Ҫ����ı���****/
/***ʹ�ô�����ʾ�ı�����Ӧ��Ϊ�����˲����ֱ������RMS��***/

extern float O_AC_current_measured ;  // ����ģʽ������ʾ
extern float O_AC_voltage_measured ;  // ����ģʽ��ѹ��ʾ

extern float AC_current_measured ;  		//  ����ģʽ������ʾ
extern float AC_voltage_measured ;  		//  ����ģʽ��ѹ��ʾ

extern float DC_voltage_measured ; 			// ֱ�����ѹ��ʾ

/****�弶���ó�ʼ��****/
void BSP_Init(void);
/****�û�������****/
void Menu(void);

#endif /* __MENU_H */
