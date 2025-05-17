#include "ControlLoop.h"

#define VDDA_Real 3.30f // 每次增加/减少 100mA
ADCData_t adc_data;

// ADC 注入采样完成中断回调函数
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1)
    {
        // 读取注入通道数据
        adc_data.raw[0] = hadc1.Instance->JDR1; // AC_V**交流侧电压
        adc_data.raw[1] = hadc1.Instance->JDR2; // DC_V**直流测电压
    }
    else if (hadc == &hadc2)
    {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);    //通过示波器监测翻转GPIO时间来看算法执行时间
		
        adc_data.raw[2] = hadc2.Instance->JDR1; //IL  **逆变电感电流，优先触发采集
		
		/**模拟采样数据恢复**/
	#if INV == 1//逆变器1参数
    adc_data.AC_V = ((adc_data.raw[0] * VDDA_Real / 4095.0f) - 1.6461f) * 50.104f;				 //交流测电压数据 50.104f
	adc_data.DC_V =   adc_data.raw[1] * VDDA_Real / 4095.0f * 21.50f; 						     // 直流侧电压数据
	adc_data.IL   = ((adc_data.raw[2] * VDDA_Real / 4095.0f) - 1.6511f) * 5.02f;                 // 交流侧电流数据5.02f
	#else//逆变器2参数
    adc_data.AC_V = ((adc_data.raw[0] * VDDA_Real / 4095.0f) - 1.6495f) * 50.104f;				 //交流测电压数据
	adc_data.DC_V =   adc_data.raw[1] * VDDA_Real / 4095.0f * 21.50f; 						     // 直流侧电压数据
	adc_data.IL   = ((adc_data.raw[2] * VDDA_Real / 4095.0f) - 1.6511f) * 5.01f;                  // 交流侧电流数据	
	#endif
       
		Uo_fb  = adc_data.AC_V;
		IL_fb = adc_data.IL;
        // 调用控制算法
        BDA_Control_step();
		
        // 设置 PWM 占空比
		TIM1->CCR1 = Duty_L*8500.0f;
        TIM1->CCR2 = Duty_R*8500.0f;
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);     //通过示波器监测翻转GPIO时间来看算法执行时间

        // 滤波处理等放在算法处理之后进行
        // 调用一阶IIR低通滤波函数
		adc_filter_update(0, adc_data.DC_V);							//直流侧电压
		
		adc_filter_update(1, -O_Uq);							        //并网模式电压
		adc_filter_update(2, -O_Iq);							        //并网模式电流
		
		/***********电压电流传感器调零***********/
		
//		adc_filter_update(3, adc_data.AC_V); 
//		adc_filter_update(4, adc_data.IL);

		/**********************************/
        adc_filter_update(3, F_Ud);                             // 离网模式交流侧电压
        adc_filter_update(4, F_Id-0.031f);                       // 离网模式交流侧电流
		
        // 获取滤波后值传到菜单显示
        DC_voltage_measured = get_filtered_value(0); 	// 直流侧电压
		
		O_AC_voltage_measured = get_filtered_value(1);	// 并网模式交流侧电压
		O_AC_current_measured = get_filtered_value(2);  //并网模式交流侧电压
		
		AC_voltage_measured = get_filtered_value(3);    // 离网模式交流侧电压
        AC_current_measured = get_filtered_value(4);	// 离网交流侧电流
        
        
    }
}
