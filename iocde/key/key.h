/*
 * key.h
 *�ú�����10msʱ��Ƭ������
 *  Created on: Feb 8, 2024
 *      Author: HXP119
 */

#ifndef KEY_KEY_H_
#define KEY_KEY_H_

/**�ú�����10msʱ��Ƭ������**/

#include "stm32g4xx_hal.h" //HAL���ļ�����
#include "main.h" //IO�������ʼ��������main.c�ļ��У���������

#define KEY1 HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin)			    //�������޸Ĵ˴�����������/���ٰ�������
#define KEY2 HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin)            //�������޸Ĵ˴�����������/���ٰ�������
#define KEY3 HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin)				//�������޸Ĵ˴�����������/���ٰ�������
//#define KEY4 HAL_GPIO_ReadPin(KEY_4_GPIO_Port, KEY_4_Pin)           	//�������޸Ĵ˴�����������/���ٰ�������

#define KEY_TIMER_SET 10 									//���������ʱ��10MS
#define REPEAT_KEY_TIME 20                                  // ����������ÿ200ms����һ�γ���״̬

#define KEY_STATE_0 0 										//����״̬
#define KEY_STATE_1 1
#define KEY_STATE_2 2
#define KEY_STATE_3 3

#define LONG_KEY_TIME 80 								//�ж�����ʱ�䣺LONG_KEY_TIME*10MS = 1000MS
#define SINGLE_KEY_TIME 1 								//�ж�����ʱ�䣺SINGLE_KEY_TIME*10MS = 10MS
#define DOUBLE_KEY_TIME 40 								//�ж�˫��ʱ�䣺DOUBLE_KEY_TIME*10MS = 500MS

#define None_click 0 											//�ް���  	����ֵ��0
#define Single_click 1 										//����		����ֵ��1
#define Double_click 2										//˫��		����ֵ��2
#define Long_click 3 											//����		����ֵ��3

#define uchar unsigned char
#define uint unsigned int

#define Key1_Single_Click 11							//�������޸Ĵ˴�����������/���ٰ�������
#define Key1_Double_Click 12							//�������޸Ĵ˴�����������/���ٰ�������
#define Key1_Long_Click 13								//�������޸Ĵ˴�����������/���ٰ�������

#define Key2_Single_Click 21							//�������޸Ĵ˴�����������/���ٰ�������
#define Key2_Double_Click 22							//�������޸Ĵ˴�����������/���ٰ�������
#define Key2_Long_Click 23								//�������޸Ĵ˴�����������/���ٰ�������

#define Key3_Single_Click 31							//�������޸Ĵ˴�����������/���ٰ�������
#define Key3_Double_Click 32							//�������޸Ĵ˴�����������/���ٰ�������
#define Key3_Long_Click 33								//�������޸Ĵ˴�����������/���ٰ�������

#define Key4_Single_Click 41							//�������޸Ĵ˴�����������/���ٰ�������
#define Key4_Double_Click 42							//�������޸Ĵ˴�����������/���ٰ�������
#define Key4_Long_Click 43								//�������޸Ĵ˴�����������/���ٰ�������

unsigned char key_multi(void);						    //�๦�ܰ���ɨ�躯�������� ��ֵ+������ ����ֵ
unsigned char keyscan(void);							//��ͨ����ɨ�躯�������� ��ֵ

#endif /* KEY_KEY_H_ */
