/*
 * key.h
 *该函数在10ms时间片下运行
 *  Created on: Feb 8, 2024
 *      Author: HXP119
 */

#ifndef KEY_KEY_H_
#define KEY_KEY_H_

/**该函数在10ms时间片下运行**/

#include "stm32g4xx_hal.h" //HAL库文件声明
#include "main.h" //IO定义与初始化函数在main.c文件中，必须引用

#define KEY1 HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin)			    //！！！修改此处，可以增加/减少按键数量
#define KEY2 HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin)            //！！！修改此处，可以增加/减少按键数量
#define KEY3 HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin)				//！！！修改此处，可以增加/减少按键数量
//#define KEY4 HAL_GPIO_ReadPin(KEY_4_GPIO_Port, KEY_4_Pin)           	//！！！修改此处，可以增加/减少按键数量

#define KEY_TIMER_SET 10 									//赋给软件定时器10MS
#define REPEAT_KEY_TIME 20                                  // 长按连发，每200ms传出一次长按状态

#define KEY_STATE_0 0 										//按键状态
#define KEY_STATE_1 1
#define KEY_STATE_2 2
#define KEY_STATE_3 3

#define LONG_KEY_TIME 80 								//判定长按时间：LONG_KEY_TIME*10MS = 1000MS
#define SINGLE_KEY_TIME 1 								//判定单击时间：SINGLE_KEY_TIME*10MS = 10MS
#define DOUBLE_KEY_TIME 40 								//判定双击时间：DOUBLE_KEY_TIME*10MS = 500MS

#define None_click 0 											//无按键  	返回值：0
#define Single_click 1 										//单击		返回值：1
#define Double_click 2										//双击		返回值：2
#define Long_click 3 											//长按		返回值：3

#define uchar unsigned char
#define uint unsigned int

#define Key1_Single_Click 11							//！！！修改此处，可以增加/减少按键数量
#define Key1_Double_Click 12							//！！！修改此处，可以增加/减少按键数量
#define Key1_Long_Click 13								//！！！修改此处，可以增加/减少按键数量

#define Key2_Single_Click 21							//！！！修改此处，可以增加/减少按键数量
#define Key2_Double_Click 22							//！！！修改此处，可以增加/减少按键数量
#define Key2_Long_Click 23								//！！！修改此处，可以增加/减少按键数量

#define Key3_Single_Click 31							//！！！修改此处，可以增加/减少按键数量
#define Key3_Double_Click 32							//！！！修改此处，可以增加/减少按键数量
#define Key3_Long_Click 33								//！！！修改此处，可以增加/减少按键数量

#define Key4_Single_Click 41							//！！！修改此处，可以增加/减少按键数量
#define Key4_Double_Click 42							//！！！修改此处，可以增加/减少按键数量
#define Key4_Long_Click 43								//！！！修改此处，可以增加/减少按键数量

unsigned char key_multi(void);						    //多功能按键扫描函数，返回 键值+键功能 复合值
unsigned char keyscan(void);							//普通按键扫描函数，返回 键值

#endif /* KEY_KEY_H_ */
