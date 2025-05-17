/*
 * menu.c
 *  Created on: Feb 8, 2025
 *      Author: HXP119
 */
#include "menu.h"
/****最大最小输出状态变量定义****/
#define OUTPUT_CURRENT_MAX 4.0f // 最大电流值，单位 A
#define OUTPUT_CURRENT_MIN 1.0f // 最小电流值，单位 A

#define OUTPUT_AC_V_MAX 30.0f // 最大交流输出电压值，单位 V
#define OUTPUT_AC_V_MIN 18.0f // 最小交流输出电压值，单位 V

/***按键及显示状态机参数***/
volatile uint8_t Key_state_switch = 0, Key_event = 0; /****键值提取和按键事件****/
volatile SystemState menu_current_state = STATE_IDLE; /****[OLED显示与功能状态机]之现在的状态****/
SystemState menu_last_state = STATE_IDLE;             /****状态机上一时刻的状态****/
/****参数变量设置****/
/****内部变量****/
float AC_current_set = 2.0f;  // 屏幕显示交流电流设定值
float K_Cur = 1.0f;           //电流设定比例，逆变器1：逆变器2电流
float AC_voltage_set = 30.0f; // 屏幕显示交流测电压设定值
float DC_voltage_set = 40.0f; // 屏幕显示直流设定值

/****需要传出的变量****/
float AC_current_target = 2.0f;  // 交流电流目标设定值
float AC_voltage_target = 30.0f; // 交流测电压目标设定值
float DC_voltage_target = 40.0f; // 直流测电压目标设定值

/****需要传入的变量****/
float O_AC_current_measured = 0.0f;  // 并网模式电流显示
float O_AC_voltage_measured = 0.0f;  // 并网模式电压显示

float AC_current_measured = 1.0f;  // 离网模式电流显示
float AC_voltage_measured = 0.0f;  // 离网模式电压显示

float DC_voltage_measured = 30.0f; // 直流侧电压显示
/***双向DCDC主板配置初始化***/
void BSP_Init(void)
{
    /*定时器初始化*/
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim2);
    /*ADC自校准*/
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
    /*默认不开启PWM，在算法启动时再开启*/
    // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    // HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
    // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    // HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
    /*开启片内运放*/
    HAL_OPAMP_Start(&hopamp2);
    /*开启TIM1_CH4的PWM触发ADC*/
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    /*ADC注入中断初始化*/
    HAL_ADCEx_InjectedStart_IT(&hadc1);
    HAL_ADCEx_InjectedStart_IT(&hadc2);
    /*一阶IIR滤波器初始化*/
    init_filter_channel(0, 10000, 5); // 滤波器0初始化，离散频率10K，低通频率5HZ
    init_filter_channel(1, 10000, 5);
    init_filter_channel(2, 10000, 5);
	init_filter_channel(3, 10000, 5);
	init_filter_channel(4, 10000, 5);
    /*算法函数初始化*/
	BDA_Control_initialize();
    /*等待配置稳定*/
    HAL_Delay(200);
    /*初始化OLED屏幕显示*/
    OLED_Init();
}
/*** PWM通道输出使能 ***/
// 启用 PWM 输出（CH1,CH2 和 CH1N,CH2N），修改其他通道的话交给AI
void EnableAllPWM(void)
{
    // 启用 CH1 和 CH1N（PWM模式1）
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM1->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);     // OC1M = 6 -> PWM Mode 1
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE; // 保证 CH1 和 CH1N 输出使能
    // 启用 CH2 和 CH2N（PWM模式1）
    TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM1->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos);     // OC2M = 6 -> PWM Mode 1
    TIM1->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2NE; // 保证 CH2 和 CH2N 输出使能
    // 主输出使能（MOE）
    TIM1->BDTR |= TIM_BDTR_MOE;
    // 立即更新寄存器
    TIM1->EGR |= TIM_EGR_UG;
}
// 禁用 PWM 输出（CH1,CH2 和 CH1N,CH2N 立马 拉低）
void DisableAllPWM(void)
{
    //  CH1 & CH1N 强制低电平
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;    // OC1M = 0 (Frozen)
    TIM1->CCER &= ~(TIM_CCER_CC1E      // CC1E = 0
                    | TIM_CCER_CC1NE); // CC1NE = 0
    //  CH2 & CH2N 强制低电平
    TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;    // OC2M = 0 (Frozen)
    TIM1->CCER &= ~(TIM_CCER_CC2E      // CC2E = 0
                    | TIM_CCER_CC2NE); // CC2NE = 0
    // 主输出保持开启（MOE）
    TIM1->BDTR |= TIM_BDTR_MOE;
    // 立即更新寄存器
    TIM1->EGR |= TIM_EGR_UG;
}
/*** 处理按键事件，控制菜单状态切换及变量操作 ***/
void HandleKeyEvent(void)
{
    if (Key_event == 0) // 无按键事件下处理限幅过压等事件，返回默认状态
    {

        return; // 无按键事件则直接返回
    }
    switch (menu_current_state) // 按键事件下进行模式选择，驱动状态机运行
    {
    case STATE_IDLE:        // 空闲状态
        if (Key_event == 1) // 按键1：进入离网模式
        {
			HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_SET);//吸合继电器
			Mode_Ch=1;
            EnableAllPWM();
            menu_current_state = STATE_OFF_GRID;
        }
        else if (Key_event == 2) // 按键2：进入双向稳压模式
        {
        }
        else if (Key_event == 3) // 按键3：进入并网模式
        {
            EnableAllPWM();
			Mode_Ch=2;
			HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_SET);//吸合继电器
			menu_current_state = STATE_ON_GRID;
        }
        else
            menu_current_state = STATE_IDLE; // 其他情况保持不变
        break;

    case STATE_ON_GRID:     // 并网模式--电流源模式
        if (Key_event == 2) // 单击按键2：进入电流设置模式
        {
            menu_current_state = STATE_O_CURSET; // 单击按键2：进入电流设置模式
        }
        else if (Key_event == 22) // 双击按键2：返回空闲状态/*复位参数*/
        {
            DisableAllPWM();                    /**关闭PWM**/
            Mode_Ch=3;
			HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_RESET);//吸合继电器
            menu_current_state = STATE_IDLE; // 回到空闲等待状态
            AC_current_set = 2.0f;       // 恢复参数
            AC_current_target = 1.0f;    // 恢复参数
            K_Cur = 1.0f;
            O_IL_ref = 1.41421f;                  // 恢复参数
        }
        else
            menu_current_state = STATE_ON_GRID; // 其他保持当前状态
        break;

    case STATE_O_CURSET:       // 并网逆变模式电流设置
                             // 若需要增加或减少电流可在此添加
        if (Key_event == 34) // 长按3：连续增加电流0.05
        {
            AC_current_set += 0.05f;  
		if (AC_current_set > OUTPUT_CURRENT_MAX) {
			AC_current_set = OUTPUT_CURRENT_MAX;
		}
        }
        else if (Key_event == 33) // 双击3：增加电流0.1
        {
           AC_current_set += 0.1f;  
		if (AC_current_set > OUTPUT_CURRENT_MAX) {
			AC_current_set = OUTPUT_CURRENT_MAX;
		}
        }
        else if (Key_event == 3) // 单击3：增加电流
        {
            AC_current_set += 0.05f;  
		if (AC_current_set > OUTPUT_CURRENT_MAX) {
			AC_current_set = OUTPUT_CURRENT_MAX;
		}
        }
        else if (Key_event == 14) // 长按1：连续减少电流0.05
        {
            AC_current_set -= 0.05f;  
		if (AC_current_set < OUTPUT_CURRENT_MIN) {
			AC_current_set = OUTPUT_CURRENT_MIN;
		}
        }
        else if (Key_event == 11) // 双击1：减少电流0.1
        {
            AC_current_set -= 0.1f;  
		if (AC_current_set < OUTPUT_CURRENT_MIN) {
			AC_current_set = OUTPUT_CURRENT_MIN;
		}
        }
        else if (Key_event == 1) // 单击1：减少电流0.05
        {
		AC_current_set -= 0.05f;  
		if (AC_current_set < OUTPUT_CURRENT_MIN) {
			AC_current_set = OUTPUT_CURRENT_MIN;
		}

        }
        else if (Key_event == 2) // 单击2：进入K值设定
        {
            menu_current_state = STATE_O_K_SET;
			AC_current_target = AC_current_set;
        }
        else
            menu_current_state = STATE_O_CURSET;
        break;
    case STATE_O_K_SET: 
        if (Key_event == 33) // 双击3：增加电流0.1
        {
             K_Cur += 0.1f;             // 先无条件加
			if (K_Cur > 2.0f)          // 再钳到上限
			K_Cur = 2.0f;
        }
        else if (Key_event == 3) // 单击3：增加电流
        {
            K_Cur += 0.05f;             // 先无条件加
			if (K_Cur > 2.0f)          // 再钳到上限
			K_Cur = 2.0f;
        }
        else if (Key_event == 1) // 单击1：0.05
        {
			K_Cur -= 0.05f;             // 先无条件减
			if (K_Cur < 0.50f)          // 再钳到下限
			K_Cur = 0.50f;

        }
        else if (Key_event == 11) // 双击1：减少电流0.1
        {
            K_Cur -= 0.1f;             // 先无条件减
			if (K_Cur < 0.50f)          // 再钳到下限
			K_Cur = 0.50f;
        }
        else if (Key_event == 22) // 双击2：返回电流调节模式
        {
            menu_current_state = STATE_O_CURSET;
        }
        else if (Key_event == 2) // 单击2：设定值保存更新并返回充电模式
        {
            menu_current_state = STATE_ON_GRID;
            AC_current_target = AC_current_set;     // 在确认后刷新电流给定值
			#if INV == 1//逆变器1电流设定
			O_IL_ref = 1.4421f* K_Cur*AC_current_target/(1+K_Cur);  // 在确认后送到控制函数目标值逆变器1计算方式
			#else//逆变器2电流设定
			O_IL_ref = 1.4421f*AC_current_target/(1+K_Cur);// 在确认后送到控制函数目标值逆变器2计算方式
			#endif  
        }
        else
        menu_current_state = STATE_O_K_SET;
        break;
    case STATE_OFF_GRID:           // 离网模式状态选择

        if (Key_event == 22) // 双击按键2：返回空闲状态/*复位参数*/
        {
            DisableAllPWM();    
			Mode_Ch=3;				// 停止控制函数使能
            HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_RESET);//松开继电器
            menu_current_state = STATE_IDLE; // 回到空闲等待状态
        }
        else
            menu_current_state = STATE_OFF_GRID;
        break;
    }

    Key_event = 0; // 清除按键事件，等待下次触发
}

/*** OLED 显示当前菜单状态与数据 ***/
void OLED_Display_State(void)
{
    switch (menu_current_state)
    {
    case STATE_IDLE: // 空闲模式显示
        OLED_ShowString(19, 0, "Mode Select", OLED_8X16);
        OLED_ReverseArea(19, 2, 87, 14);
        OLED_ShowString(0, 16, "OFGD", OLED_8X16);
        OLED_ShowString(96, 16, "ONGD", OLED_8X16);
	/***传感器调零显示界面***/
//      OLED_Printf(0, 16, OLED_8X16, "Vout:%.3fV", AC_voltage_measured); // 显示采集滤波后电压实际值
//		OLED_Printf(0, 0, OLED_6X8, "Iout:%.3fA", AC_current_measured);   // 显示采集滤波后电流实际值
        break;

    case STATE_ON_GRID: // 并网模式显示
        OLED_ShowString(0, 0, "ONGD", OLED_8X16);
		OLED_Printf(40,0, OLED_8X16, "Iall:%.2fA", AC_current_set); // 显示电流设定的值
		#if INV == 1//逆变器1电流显示
		OLED_Printf(0, 16, OLED_8X16, "I:%.2fA",  K_Cur*AC_current_target/(1+K_Cur)); // 显示会输出的电流值，逆变器1计算方式
		#else//逆变器2电流显示
		OLED_Printf(0, 16, OLED_8X16, "I:%.2fA", AC_current_target/(1+K_Cur)); // 显示会输出的电流值，逆变器2计算方式
		#endif  
		OLED_Printf(75, 16, OLED_8X16, "K:%.2f", K_Cur); // 显示电流设定的值
		OLED_DrawLine(36,0,36,16);
		OLED_DrawLine(0,16,127,16);
		OLED_DrawLine(65,16,65,32);
        break;

    case STATE_O_CURSET: // 设置电流模式显示
        OLED_ShowString(0, 0, "Current Set", OLED_8X16);
        OLED_Printf(0, 16, OLED_8X16, "Iset:%.2fA", AC_current_set); // 显示电流设定的值
        break;
    case STATE_O_K_SET: // 设置电流模式显示
        OLED_ShowString(0, 0, "K Set", OLED_8X16);
        OLED_Printf(0, 16, OLED_8X16, "K:%.2f", K_Cur); // 显示电流设定的值
		#if INV == 1//逆变器1电流显示
		OLED_Printf(60, 16, OLED_8X16, "I:%.2fA", K_Cur*AC_current_target/(1+K_Cur)); // 显示会输出的电流值，逆变器1计算方式
		#else//逆变器2电流显示
		OLED_Printf(60, 16, OLED_8X16, "I:%.2fA", AC_current_target/(1+K_Cur)); // 显示会输出的电流值，逆变器2计算方式
		#endif  
        break;
    case STATE_OFF_GRID: // 离网逆变模式显示
        OLED_ShowString(96, 0, "OFGD", OLED_8X16);
        OLED_Printf(0, 16, OLED_8X16, "Vout:%.3fV", AC_voltage_measured); // 显示采集滤波后电压实际值
		if(AC_current_measured<=0)
		{
			OLED_Printf(0, 0, OLED_6X8, "Iout:0.00A");   // 显示采集滤波后电流实际值
		}else
		{
		  OLED_Printf(0, 0, OLED_6X8, "Iout:%.3fA",AC_current_measured);   // 显示采集滤波后电流实际值
		}
        break;
    }
}

/*** 菜单主循环函数 ***/
void Menu(void)
{
    while (1)
    {
        if (menu_current_state != menu_last_state)
        {
            OLED_Clear(); // 状态改变时清屏
            menu_last_state = menu_current_state;
        }
        HandleKeyEvent();     // 处理按键事件
        OLED_Display_State(); // 显示当前状态
        OLED_Update();        // 更新OLED显示
        HAL_Delay(50);        // 稍作延时，避免闪烁
    }
}

/*** 定时器中断回调函数，用于按键扫描和LED闪烁 ***/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint16_t TIM2_Cnt1 = 1, TIM2_Cnt2 = 1;

    if (htim->Instance == TIM2) // 判断是TIM2触发的中断
    {
        TIM2_Cnt1++;
        TIM2_Cnt2++;

        /*** 每10ms进行一次按键扫描 ***/
        if (TIM2_Cnt1 >= 10)
        {
            Key_state_switch = key_multi(); // 扫描按键状态

            if (Key_state_switch == Key1_Single_Click)
            {
                Key_event = 1; // 按键1 单击
                               //                HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin); // 指示灯翻转
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key2_Single_Click)
            {
                Key_event = 2; // 按键2 单击
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key3_Single_Click)
            {
                Key_event = 3; // 按键3 单击
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key1_Double_Click)
            {
                Key_event = 11; // 按键1 双击
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key2_Double_Click)
            {
                Key_event = 22; // 按键2 双击
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key3_Double_Click)
            {
                Key_event = 33; // 按键3 双击
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key1_Long_Click)
            {
                Key_event = 14; // 按键1 长按
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key3_Long_Click)
            {
                Key_event = 34; // 按键3 长按
                Key_state_switch = 0;
            }

            TIM2_Cnt1 = 1; // 重置计数器
        }

        /*** 每500ms翻转一次绿灯，作为运行指示灯 ***/
        if (TIM2_Cnt2 >= 500)
        {
            TIM2_Cnt2 = 1;
            HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        }
    }
}
/*********************************************************************************************
*********************************************************************************************/
