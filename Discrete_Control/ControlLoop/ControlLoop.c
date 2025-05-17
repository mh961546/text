#include "ControlLoop.h"

#define VDDA_Real 3.30f // ÿ������/���� 100mA
ADCData_t adc_data;

// ADC ע���������жϻص�����
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1)
    {
        // ��ȡע��ͨ������
        adc_data.raw[0] = hadc1.Instance->JDR1; // AC_V**�������ѹ
        adc_data.raw[1] = hadc1.Instance->JDR2; // DC_V**ֱ�����ѹ
    }
    else if (hadc == &hadc2)
    {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);    //ͨ��ʾ������ⷭתGPIOʱ�������㷨ִ��ʱ��
		
        adc_data.raw[2] = hadc2.Instance->JDR1; //IL  **����е��������ȴ����ɼ�
		
		/**ģ��������ݻָ�**/
	#if INV == 1//�����1����
    adc_data.AC_V = ((adc_data.raw[0] * VDDA_Real / 4095.0f) - 1.6461f) * 50.104f;				 //�������ѹ���� 50.104f
	adc_data.DC_V =   adc_data.raw[1] * VDDA_Real / 4095.0f * 21.50f; 						     // ֱ�����ѹ����
	adc_data.IL   = ((adc_data.raw[2] * VDDA_Real / 4095.0f) - 1.6511f) * 5.02f;                 // �������������5.02f
	#else//�����2����
    adc_data.AC_V = ((adc_data.raw[0] * VDDA_Real / 4095.0f) - 1.6495f) * 50.104f;				 //�������ѹ����
	adc_data.DC_V =   adc_data.raw[1] * VDDA_Real / 4095.0f * 21.50f; 						     // ֱ�����ѹ����
	adc_data.IL   = ((adc_data.raw[2] * VDDA_Real / 4095.0f) - 1.6511f) * 5.01f;                  // �������������	
	#endif
       
		Uo_fb  = adc_data.AC_V;
		IL_fb = adc_data.IL;
        // ���ÿ����㷨
        BDA_Control_step();
		
        // ���� PWM ռ�ձ�
		TIM1->CCR1 = Duty_L*8500.0f;
        TIM1->CCR2 = Duty_R*8500.0f;
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);     //ͨ��ʾ������ⷭתGPIOʱ�������㷨ִ��ʱ��

        // �˲�����ȷ����㷨����֮�����
        // ����һ��IIR��ͨ�˲�����
		adc_filter_update(0, adc_data.DC_V);							//ֱ�����ѹ
		
		adc_filter_update(1, -O_Uq);							        //����ģʽ��ѹ
		adc_filter_update(2, -O_Iq);							        //����ģʽ����
		
		/***********��ѹ��������������***********/
		
//		adc_filter_update(3, adc_data.AC_V); 
//		adc_filter_update(4, adc_data.IL);

		/**********************************/
        adc_filter_update(3, F_Ud);                             // ����ģʽ�������ѹ
        adc_filter_update(4, F_Id-0.031f);                       // ����ģʽ���������
		
        // ��ȡ�˲���ֵ�����˵���ʾ
        DC_voltage_measured = get_filtered_value(0); 	// ֱ�����ѹ
		
		O_AC_voltage_measured = get_filtered_value(1);	// ����ģʽ�������ѹ
		O_AC_current_measured = get_filtered_value(2);  //����ģʽ�������ѹ
		
		AC_voltage_measured = get_filtered_value(3);    // ����ģʽ�������ѹ
        AC_current_measured = get_filtered_value(4);	// �������������
        
        
    }
}
