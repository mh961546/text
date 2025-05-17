// ControlLoop.h
#ifndef __CONTROL_LOOP_H
#define __CONTROL_LOOP_H

#include "adc.h"       // 因为使用到ADC中断，在这里引用
#include "tim.h"       //
#include "Ownfliter.h" //滤波函数调用
#include "menu.h"      //传出采集到的变量到菜单，同时传入指令
#include "BDA_Control.h"
#define INV 1
typedef struct
{
    uint16_t raw[4]; // 原始 ADC 值
    float AC_V;       // ADC1注入通道1 - 交流侧电压
    float DC_V;       // ADC1注入通道2 - 直流侧电压
	
	float IL;         // ADC2注入通道1 - 电感电流
    float VREF;       // ADC2注入通道2 - 参考电压

} ADCData_t;

extern ADCData_t adc_data;
// 变量声明

extern uint16_t CCR_out;

// 函数声明
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);

#endif // __CONTROL_LOOP_H
