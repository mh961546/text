// ControlLoop.h
#ifndef __CONTROL_LOOP_H
#define __CONTROL_LOOP_H

#include "adc.h"       // ��Ϊʹ�õ�ADC�жϣ�����������
#include "tim.h"       //
#include "Ownfliter.h" //�˲���������
#include "menu.h"      //�����ɼ����ı������˵���ͬʱ����ָ��
#include "BDA_Control.h"
#define INV 1
typedef struct
{
    uint16_t raw[4]; // ԭʼ ADC ֵ
    float AC_V;       // ADC1ע��ͨ��1 - �������ѹ
    float DC_V;       // ADC1ע��ͨ��2 - ֱ�����ѹ
	
	float IL;         // ADC2ע��ͨ��1 - ��е���
    float VREF;       // ADC2ע��ͨ��2 - �ο���ѹ

} ADCData_t;

extern ADCData_t adc_data;
// ��������

extern uint16_t CCR_out;

// ��������
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);

#endif // __CONTROL_LOOP_H
