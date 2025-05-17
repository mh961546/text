// Ownfliter.c
#include "Ownfliter.h"

// 定义四个通道的滤波器
static FilterChannel filter_channels[5];

// 初始化滤波器（设置截止频率）
void set_filter_cutoff(uint8_t channel_id, float new_fc)
{
    if (channel_id >= 5)
        return; // 确保通道 ID 在有效范围内

    if (new_fc < 5.0f)
        new_fc = 5.0f;
    if (new_fc > 100.0f)
        new_fc = 100.0f;

    FilterChannel *channel = &filter_channels[channel_id];
    channel->fc = new_fc;
    float tau = 1.0f / (2.0f * 3.1415926f * channel->fc);
    channel->alpha = 1.0f / (1.0f + (channel->fs * tau));
}

void init_filter_channel(uint8_t id, float fs, float fc)
{
    if (id >= 5)
        return;
    filter_channels[id].fs = fs;
    set_filter_cutoff(id, fc); // set_filter_cutoff 会计算 alpha
}

// 滤波处理函数（在中断中调用）
void adc_filter_update(uint8_t channel_id, float adc_raw)
{
    if (channel_id >= 5)
        return; // 确保通道 ID 在有效范围内

    FilterChannel *channel = &filter_channels[channel_id];
    float adc_in = (float)adc_raw;
    channel->adc_filtered = channel->alpha * adc_in + (1.0f - channel->alpha) * channel->adc_filtered;
}

// 获取当前滤波后的结果
float get_filtered_value(uint8_t channel_id)
{
    if (channel_id >= 5)
        return 0.0f; // 确保通道 ID 在有效范围内

    return filter_channels[channel_id].adc_filtered;
}
