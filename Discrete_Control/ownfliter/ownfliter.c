// Ownfliter.c
#include "Ownfliter.h"

// �����ĸ�ͨ�����˲���
static FilterChannel filter_channels[5];

// ��ʼ���˲��������ý�ֹƵ�ʣ�
void set_filter_cutoff(uint8_t channel_id, float new_fc)
{
    if (channel_id >= 5)
        return; // ȷ��ͨ�� ID ����Ч��Χ��

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
    set_filter_cutoff(id, fc); // set_filter_cutoff ����� alpha
}

// �˲������������ж��е��ã�
void adc_filter_update(uint8_t channel_id, float adc_raw)
{
    if (channel_id >= 5)
        return; // ȷ��ͨ�� ID ����Ч��Χ��

    FilterChannel *channel = &filter_channels[channel_id];
    float adc_in = (float)adc_raw;
    channel->adc_filtered = channel->alpha * adc_in + (1.0f - channel->alpha) * channel->adc_filtered;
}

// ��ȡ��ǰ�˲���Ľ��
float get_filtered_value(uint8_t channel_id)
{
    if (channel_id >= 5)
        return 0.0f; // ȷ��ͨ�� ID ����Ч��Χ��

    return filter_channels[channel_id].adc_filtered;
}
