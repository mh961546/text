#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*�ַ�������*/
/*���������궨��ֻ�ɽ������һ����ע��*/
//#define OLED_CHARSET_UTF8			//�����ַ���ΪUTF8
#define OLED_CHARSET_GB2312		//�����ַ���ΪGB2312

/*��ģ������Ԫ1*/
typedef struct 
{
	
#ifdef OLED_CHARSET_UTF8			//�����ַ���ΪUTF8
	char Index[5];					//�����������ռ�Ϊ5�ֽ�
#endif
	
#ifdef OLED_CHARSET_GB2312			//�����ַ���ΪGB2312
	char Index[3];					//�����������ռ�Ϊ3�ֽ�
#endif
    uint8_t Data16x16[32];           // �洢16x16��ģ���ݣ�32�ֽڣ�
} ChineseCell_t;
/*��ģ������Ԫ2*/
typedef struct 
{
	
#ifdef OLED_CHARSET_UTF8			//�����ַ���ΪUTF8
	char Index[5];					//�����������ռ�Ϊ5�ֽ�
#endif
	
#ifdef OLED_CHARSET_GB2312			//�����ַ���ΪGB2312
	char Index[3];					//�����������ռ�Ϊ3�ֽ�
#endif
    uint8_t Data12x12[24];           // �洢12x12��ģ���ݣ�18�ֽڣ�
} ChineseCell_m;

/*ASCII��ģ��������*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*������ģ��������*/
extern const ChineseCell_t OLED_CF16x16[];
extern const ChineseCell_m OLED_CF12x12[];
/*ͼ����������*/
extern const uint8_t Diode[];
/*��������ĸ�ʽ�������λ�ü����µ�ͼ����������*/
//...

#endif

