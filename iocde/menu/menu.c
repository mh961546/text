/*
 * menu.c
 *  Created on: Feb 8, 2025
 *      Author: HXP119
 */
#include "menu.h"
/****�����С���״̬��������****/
#define OUTPUT_CURRENT_MAX 4.0f // ������ֵ����λ A
#define OUTPUT_CURRENT_MIN 1.0f // ��С����ֵ����λ A

#define OUTPUT_AC_V_MAX 30.0f // ����������ѹֵ����λ V
#define OUTPUT_AC_V_MIN 18.0f // ��С���������ѹֵ����λ V

/***��������ʾ״̬������***/
volatile uint8_t Key_state_switch = 0, Key_event = 0; /****��ֵ��ȡ�Ͱ����¼�****/
volatile SystemState menu_current_state = STATE_IDLE; /****[OLED��ʾ�빦��״̬��]֮���ڵ�״̬****/
SystemState menu_last_state = STATE_IDLE;             /****״̬����һʱ�̵�״̬****/
/****������������****/
/****�ڲ�����****/
float AC_current_set = 2.0f;  // ��Ļ��ʾ���������趨ֵ
float K_Cur = 1.0f;           //�����趨�����������1�������2����
float AC_voltage_set = 30.0f; // ��Ļ��ʾ�������ѹ�趨ֵ
float DC_voltage_set = 40.0f; // ��Ļ��ʾֱ���趨ֵ

/****��Ҫ�����ı���****/
float AC_current_target = 2.0f;  // ��������Ŀ���趨ֵ
float AC_voltage_target = 30.0f; // �������ѹĿ���趨ֵ
float DC_voltage_target = 40.0f; // ֱ�����ѹĿ���趨ֵ

/****��Ҫ����ı���****/
float O_AC_current_measured = 0.0f;  // ����ģʽ������ʾ
float O_AC_voltage_measured = 0.0f;  // ����ģʽ��ѹ��ʾ

float AC_current_measured = 1.0f;  // ����ģʽ������ʾ
float AC_voltage_measured = 0.0f;  // ����ģʽ��ѹ��ʾ

float DC_voltage_measured = 30.0f; // ֱ�����ѹ��ʾ
/***˫��DCDC�������ó�ʼ��***/
void BSP_Init(void)
{
    /*��ʱ����ʼ��*/
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim2);
    /*ADC��У׼*/
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
    /*Ĭ�ϲ�����PWM�����㷨����ʱ�ٿ���*/
    // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    // HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
    // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    // HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
    /*����Ƭ���˷�*/
    HAL_OPAMP_Start(&hopamp2);
    /*����TIM1_CH4��PWM����ADC*/
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    /*ADCע���жϳ�ʼ��*/
    HAL_ADCEx_InjectedStart_IT(&hadc1);
    HAL_ADCEx_InjectedStart_IT(&hadc2);
    /*һ��IIR�˲�����ʼ��*/
    init_filter_channel(0, 10000, 5); // �˲���0��ʼ������ɢƵ��10K����ͨƵ��5HZ
    init_filter_channel(1, 10000, 5);
    init_filter_channel(2, 10000, 5);
	init_filter_channel(3, 10000, 5);
	init_filter_channel(4, 10000, 5);
    /*�㷨������ʼ��*/
	BDA_Control_initialize();
    /*�ȴ������ȶ�*/
    HAL_Delay(200);
    /*��ʼ��OLED��Ļ��ʾ*/
    OLED_Init();
}
/*** PWMͨ�����ʹ�� ***/
// ���� PWM �����CH1,CH2 �� CH1N,CH2N�����޸�����ͨ���Ļ�����AI
void EnableAllPWM(void)
{
    // ���� CH1 �� CH1N��PWMģʽ1��
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM1->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);     // OC1M = 6 -> PWM Mode 1
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE; // ��֤ CH1 �� CH1N ���ʹ��
    // ���� CH2 �� CH2N��PWMģʽ1��
    TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM1->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos);     // OC2M = 6 -> PWM Mode 1
    TIM1->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2NE; // ��֤ CH2 �� CH2N ���ʹ��
    // �����ʹ�ܣ�MOE��
    TIM1->BDTR |= TIM_BDTR_MOE;
    // �������¼Ĵ���
    TIM1->EGR |= TIM_EGR_UG;
}
// ���� PWM �����CH1,CH2 �� CH1N,CH2N ���� ���ͣ�
void DisableAllPWM(void)
{
    //  CH1 & CH1N ǿ�Ƶ͵�ƽ
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;    // OC1M = 0 (Frozen)
    TIM1->CCER &= ~(TIM_CCER_CC1E      // CC1E = 0
                    | TIM_CCER_CC1NE); // CC1NE = 0
    //  CH2 & CH2N ǿ�Ƶ͵�ƽ
    TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;    // OC2M = 0 (Frozen)
    TIM1->CCER &= ~(TIM_CCER_CC2E      // CC2E = 0
                    | TIM_CCER_CC2NE); // CC2NE = 0
    // ��������ֿ�����MOE��
    TIM1->BDTR |= TIM_BDTR_MOE;
    // �������¼Ĵ���
    TIM1->EGR |= TIM_EGR_UG;
}
/*** �������¼������Ʋ˵�״̬�л����������� ***/
void HandleKeyEvent(void)
{
    if (Key_event == 0) // �ް����¼��´����޷���ѹ���¼�������Ĭ��״̬
    {

        return; // �ް����¼���ֱ�ӷ���
    }
    switch (menu_current_state) // �����¼��½���ģʽѡ������״̬������
    {
    case STATE_IDLE:        // ����״̬
        if (Key_event == 1) // ����1����������ģʽ
        {
			HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_SET);//���ϼ̵���
			Mode_Ch=1;
            EnableAllPWM();
            menu_current_state = STATE_OFF_GRID;
        }
        else if (Key_event == 2) // ����2������˫����ѹģʽ
        {
        }
        else if (Key_event == 3) // ����3�����벢��ģʽ
        {
            EnableAllPWM();
			Mode_Ch=2;
			HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_SET);//���ϼ̵���
			menu_current_state = STATE_ON_GRID;
        }
        else
            menu_current_state = STATE_IDLE; // ����������ֲ���
        break;

    case STATE_ON_GRID:     // ����ģʽ--����Դģʽ
        if (Key_event == 2) // ��������2�������������ģʽ
        {
            menu_current_state = STATE_O_CURSET; // ��������2�������������ģʽ
        }
        else if (Key_event == 22) // ˫������2�����ؿ���״̬/*��λ����*/
        {
            DisableAllPWM();                    /**�ر�PWM**/
            Mode_Ch=3;
			HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_RESET);//���ϼ̵���
            menu_current_state = STATE_IDLE; // �ص����еȴ�״̬
            AC_current_set = 2.0f;       // �ָ�����
            AC_current_target = 1.0f;    // �ָ�����
            K_Cur = 1.0f;
            O_IL_ref = 1.41421f;                  // �ָ�����
        }
        else
            menu_current_state = STATE_ON_GRID; // �������ֵ�ǰ״̬
        break;

    case STATE_O_CURSET:       // �������ģʽ��������
                             // ����Ҫ���ӻ���ٵ������ڴ����
        if (Key_event == 34) // ����3���������ӵ���0.05
        {
            AC_current_set += 0.05f;  
		if (AC_current_set > OUTPUT_CURRENT_MAX) {
			AC_current_set = OUTPUT_CURRENT_MAX;
		}
        }
        else if (Key_event == 33) // ˫��3�����ӵ���0.1
        {
           AC_current_set += 0.1f;  
		if (AC_current_set > OUTPUT_CURRENT_MAX) {
			AC_current_set = OUTPUT_CURRENT_MAX;
		}
        }
        else if (Key_event == 3) // ����3�����ӵ���
        {
            AC_current_set += 0.05f;  
		if (AC_current_set > OUTPUT_CURRENT_MAX) {
			AC_current_set = OUTPUT_CURRENT_MAX;
		}
        }
        else if (Key_event == 14) // ����1���������ٵ���0.05
        {
            AC_current_set -= 0.05f;  
		if (AC_current_set < OUTPUT_CURRENT_MIN) {
			AC_current_set = OUTPUT_CURRENT_MIN;
		}
        }
        else if (Key_event == 11) // ˫��1�����ٵ���0.1
        {
            AC_current_set -= 0.1f;  
		if (AC_current_set < OUTPUT_CURRENT_MIN) {
			AC_current_set = OUTPUT_CURRENT_MIN;
		}
        }
        else if (Key_event == 1) // ����1�����ٵ���0.05
        {
		AC_current_set -= 0.05f;  
		if (AC_current_set < OUTPUT_CURRENT_MIN) {
			AC_current_set = OUTPUT_CURRENT_MIN;
		}

        }
        else if (Key_event == 2) // ����2������Kֵ�趨
        {
            menu_current_state = STATE_O_K_SET;
			AC_current_target = AC_current_set;
        }
        else
            menu_current_state = STATE_O_CURSET;
        break;
    case STATE_O_K_SET: 
        if (Key_event == 33) // ˫��3�����ӵ���0.1
        {
             K_Cur += 0.1f;             // ����������
			if (K_Cur > 2.0f)          // ��ǯ������
			K_Cur = 2.0f;
        }
        else if (Key_event == 3) // ����3�����ӵ���
        {
            K_Cur += 0.05f;             // ����������
			if (K_Cur > 2.0f)          // ��ǯ������
			K_Cur = 2.0f;
        }
        else if (Key_event == 1) // ����1��0.05
        {
			K_Cur -= 0.05f;             // ����������
			if (K_Cur < 0.50f)          // ��ǯ������
			K_Cur = 0.50f;

        }
        else if (Key_event == 11) // ˫��1�����ٵ���0.1
        {
            K_Cur -= 0.1f;             // ����������
			if (K_Cur < 0.50f)          // ��ǯ������
			K_Cur = 0.50f;
        }
        else if (Key_event == 22) // ˫��2�����ص�������ģʽ
        {
            menu_current_state = STATE_O_CURSET;
        }
        else if (Key_event == 2) // ����2���趨ֵ������²����س��ģʽ
        {
            menu_current_state = STATE_ON_GRID;
            AC_current_target = AC_current_set;     // ��ȷ�Ϻ�ˢ�µ�������ֵ
			#if INV == 1//�����1�����趨
			O_IL_ref = 1.4421f* K_Cur*AC_current_target/(1+K_Cur);  // ��ȷ�Ϻ��͵����ƺ���Ŀ��ֵ�����1���㷽ʽ
			#else//�����2�����趨
			O_IL_ref = 1.4421f*AC_current_target/(1+K_Cur);// ��ȷ�Ϻ��͵����ƺ���Ŀ��ֵ�����2���㷽ʽ
			#endif  
        }
        else
        menu_current_state = STATE_O_K_SET;
        break;
    case STATE_OFF_GRID:           // ����ģʽ״̬ѡ��

        if (Key_event == 22) // ˫������2�����ؿ���״̬/*��λ����*/
        {
            DisableAllPWM();    
			Mode_Ch=3;				// ֹͣ���ƺ���ʹ��
            HAL_GPIO_WritePin(K_CON_GPIO_Port,K_CON_Pin,GPIO_PIN_RESET);//�ɿ��̵���
            menu_current_state = STATE_IDLE; // �ص����еȴ�״̬
        }
        else
            menu_current_state = STATE_OFF_GRID;
        break;
    }

    Key_event = 0; // ��������¼����ȴ��´δ���
}

/*** OLED ��ʾ��ǰ�˵�״̬������ ***/
void OLED_Display_State(void)
{
    switch (menu_current_state)
    {
    case STATE_IDLE: // ����ģʽ��ʾ
        OLED_ShowString(19, 0, "Mode Select", OLED_8X16);
        OLED_ReverseArea(19, 2, 87, 14);
        OLED_ShowString(0, 16, "OFGD", OLED_8X16);
        OLED_ShowString(96, 16, "ONGD", OLED_8X16);
	/***������������ʾ����***/
//      OLED_Printf(0, 16, OLED_8X16, "Vout:%.3fV", AC_voltage_measured); // ��ʾ�ɼ��˲����ѹʵ��ֵ
//		OLED_Printf(0, 0, OLED_6X8, "Iout:%.3fA", AC_current_measured);   // ��ʾ�ɼ��˲������ʵ��ֵ
        break;

    case STATE_ON_GRID: // ����ģʽ��ʾ
        OLED_ShowString(0, 0, "ONGD", OLED_8X16);
		OLED_Printf(40,0, OLED_8X16, "Iall:%.2fA", AC_current_set); // ��ʾ�����趨��ֵ
		#if INV == 1//�����1������ʾ
		OLED_Printf(0, 16, OLED_8X16, "I:%.2fA",  K_Cur*AC_current_target/(1+K_Cur)); // ��ʾ������ĵ���ֵ�������1���㷽ʽ
		#else//�����2������ʾ
		OLED_Printf(0, 16, OLED_8X16, "I:%.2fA", AC_current_target/(1+K_Cur)); // ��ʾ������ĵ���ֵ�������2���㷽ʽ
		#endif  
		OLED_Printf(75, 16, OLED_8X16, "K:%.2f", K_Cur); // ��ʾ�����趨��ֵ
		OLED_DrawLine(36,0,36,16);
		OLED_DrawLine(0,16,127,16);
		OLED_DrawLine(65,16,65,32);
        break;

    case STATE_O_CURSET: // ���õ���ģʽ��ʾ
        OLED_ShowString(0, 0, "Current Set", OLED_8X16);
        OLED_Printf(0, 16, OLED_8X16, "Iset:%.2fA", AC_current_set); // ��ʾ�����趨��ֵ
        break;
    case STATE_O_K_SET: // ���õ���ģʽ��ʾ
        OLED_ShowString(0, 0, "K Set", OLED_8X16);
        OLED_Printf(0, 16, OLED_8X16, "K:%.2f", K_Cur); // ��ʾ�����趨��ֵ
		#if INV == 1//�����1������ʾ
		OLED_Printf(60, 16, OLED_8X16, "I:%.2fA", K_Cur*AC_current_target/(1+K_Cur)); // ��ʾ������ĵ���ֵ�������1���㷽ʽ
		#else//�����2������ʾ
		OLED_Printf(60, 16, OLED_8X16, "I:%.2fA", AC_current_target/(1+K_Cur)); // ��ʾ������ĵ���ֵ�������2���㷽ʽ
		#endif  
        break;
    case STATE_OFF_GRID: // �������ģʽ��ʾ
        OLED_ShowString(96, 0, "OFGD", OLED_8X16);
        OLED_Printf(0, 16, OLED_8X16, "Vout:%.3fV", AC_voltage_measured); // ��ʾ�ɼ��˲����ѹʵ��ֵ
		if(AC_current_measured<=0)
		{
			OLED_Printf(0, 0, OLED_6X8, "Iout:0.00A");   // ��ʾ�ɼ��˲������ʵ��ֵ
		}else
		{
		  OLED_Printf(0, 0, OLED_6X8, "Iout:%.3fA",AC_current_measured);   // ��ʾ�ɼ��˲������ʵ��ֵ
		}
        break;
    }
}

/*** �˵���ѭ������ ***/
void Menu(void)
{
    while (1)
    {
        if (menu_current_state != menu_last_state)
        {
            OLED_Clear(); // ״̬�ı�ʱ����
            menu_last_state = menu_current_state;
        }
        HandleKeyEvent();     // �������¼�
        OLED_Display_State(); // ��ʾ��ǰ״̬
        OLED_Update();        // ����OLED��ʾ
        HAL_Delay(50);        // ������ʱ��������˸
    }
}

/*** ��ʱ���жϻص����������ڰ���ɨ���LED��˸ ***/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint16_t TIM2_Cnt1 = 1, TIM2_Cnt2 = 1;

    if (htim->Instance == TIM2) // �ж���TIM2�������ж�
    {
        TIM2_Cnt1++;
        TIM2_Cnt2++;

        /*** ÿ10ms����һ�ΰ���ɨ�� ***/
        if (TIM2_Cnt1 >= 10)
        {
            Key_state_switch = key_multi(); // ɨ�谴��״̬

            if (Key_state_switch == Key1_Single_Click)
            {
                Key_event = 1; // ����1 ����
                               //                HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin); // ָʾ�Ʒ�ת
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key2_Single_Click)
            {
                Key_event = 2; // ����2 ����
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key3_Single_Click)
            {
                Key_event = 3; // ����3 ����
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key1_Double_Click)
            {
                Key_event = 11; // ����1 ˫��
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key2_Double_Click)
            {
                Key_event = 22; // ����2 ˫��
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key3_Double_Click)
            {
                Key_event = 33; // ����3 ˫��
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key1_Long_Click)
            {
                Key_event = 14; // ����1 ����
                Key_state_switch = 0;
            }

            if (Key_state_switch == Key3_Long_Click)
            {
                Key_event = 34; // ����3 ����
                Key_state_switch = 0;
            }

            TIM2_Cnt1 = 1; // ���ü�����
        }

        /*** ÿ500ms��תһ���̵ƣ���Ϊ����ָʾ�� ***/
        if (TIM2_Cnt2 >= 500)
        {
            TIM2_Cnt2 = 1;
            HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        }
    }
}
/*********************************************************************************************
*********************************************************************************************/
