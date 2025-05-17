/*
 * menu.h
 *  Created on: Feb 8, 2024
 *      Author: HXP119
 */

#ifndef __MENU_H
#define __MENU_H
#include "stm32g4xx_hal.h" //HAL库文件声明
#include "main.h" //IO定义与初始化函数在main.c文件中，必须引用
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
    STATE_IDLE,       // 空闲状态
    STATE_OFF_GRID,   // 离网逆变-电压源模式
    STATE_F_ACVSET,     // 离网逆变模式调输出电压

    STATE_ON_GRID,    // 并网逆变-电流源模式
	STATE_O_CURSET,     // 并网逆变模式电流设置
    STATE_O_K_SET,     // 并网逆变模式K值设置

     STATE_BDIV,       // 双向逆变器，稳直流侧电压
    
} SystemState;

extern volatile SystemState menu_current_state; // 声明全局状态变量

/****需要传出的变量****/
extern float AC_current_target;		//交流电流环目标设定值
extern float AC_voltage_target;		//交流侧电压环目标设定值
extern float DC_voltage_target;		//直流侧电压环目标设定值

/****需要传入的变量****/
/***使用传入显示的变量均应该为经过滤波后的直流或者RMS量***/

extern float O_AC_current_measured ;  // 并网模式电流显示
extern float O_AC_voltage_measured ;  // 并网模式电压显示

extern float AC_current_measured ;  		//  离网模式电流显示
extern float AC_voltage_measured ;  		//  离网模式电压显示

extern float DC_voltage_measured ; 			// 直流侧电压显示

/****板级配置初始化****/
void BSP_Init(void);
/****用户交互层****/
void Menu(void);

#endif /* __MENU_H */
