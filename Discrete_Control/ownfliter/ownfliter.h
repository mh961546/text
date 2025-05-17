// Ownfliter.h
#ifndef OWN_FILTER_H
#define OWN_FILTER_H

#include <stdint.h>

// 每个通道的滤波器结构体
typedef struct
{
    float adc_filtered; // 当前滤波后的结果
    float alpha;        // 滤波系数
    float fs;           // 采样频率
    float fc;           // 截止频率（Hz）
} FilterChannel;

// 初始化滤波器（设置截止频率，单位 Hz）
// channel_id: 0 - 4 (通道1至通道5)
void set_filter_cutoff(uint8_t channel_id, float new_fc);
void init_filter_channel(uint8_t id, float fs, float fc);

// 滤波处理函数（在中断中调用）
// channel_id: 0 - 4 (通道1至通道5)
void adc_filter_update(uint8_t channel_id, float adc_raw);

// 获取当前滤波后的结果
// channel_id: 0 - 4 (通道1至通道5)
float get_filtered_value(uint8_t channel_id);

#endif // OWN_FILTER_H
