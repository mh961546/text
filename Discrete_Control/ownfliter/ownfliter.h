// Ownfliter.h
#ifndef OWN_FILTER_H
#define OWN_FILTER_H

#include <stdint.h>

// ÿ��ͨ�����˲����ṹ��
typedef struct
{
    float adc_filtered; // ��ǰ�˲���Ľ��
    float alpha;        // �˲�ϵ��
    float fs;           // ����Ƶ��
    float fc;           // ��ֹƵ�ʣ�Hz��
} FilterChannel;

// ��ʼ���˲��������ý�ֹƵ�ʣ���λ Hz��
// channel_id: 0 - 4 (ͨ��1��ͨ��5)
void set_filter_cutoff(uint8_t channel_id, float new_fc);
void init_filter_channel(uint8_t id, float fs, float fc);

// �˲������������ж��е��ã�
// channel_id: 0 - 4 (ͨ��1��ͨ��5)
void adc_filter_update(uint8_t channel_id, float adc_raw);

// ��ȡ��ǰ�˲���Ľ��
// channel_id: 0 - 4 (ͨ��1��ͨ��5)
float get_filtered_value(uint8_t channel_id);

#endif // OWN_FILTER_H
