#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stddef.h>

#define ADC_MAGIC_NUMBER 0xADC1BEEF
#define ADC_EXPECTED_VERSION 1
#define ADC_CHANNEL_COUNT 4
#define ADC_SAMPLE_RATE_HZ 1000
#define ADC_MAX_RAW_VALUE 4095.0
#define ADC_REFERENCE_VOLTAGE 3.3

typedef struct {
    uint32_t magic;
    uint16_t version;
    uint16_t channel_count;
    uint32_t record_count;
    uint32_t sample_rate_hz;
    uint8_t reserved[8];
} ADCHeader;

#pragma pack(push, 1)
typedef struct {
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
    uint8_t reserved[2];
} ADCBinaryRecord;
#pragma pack(pop)

typedef struct {
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    double voltage;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
} ADCSample;

typedef struct {
    uint32_t missing_from;
    uint32_t missing_to;
    uint32_t previous_sequence;
    uint32_t next_sequence;
} SequenceGap;

typedef struct {
    uint8_t channel_id;
    size_t sample_count;
    double mean_voltage;
    double min_voltage;
    double max_voltage;
    double standard_deviation;
    size_t overvoltage_count;
    size_t undervoltage_count;
    size_t sensor_fault_count;
    size_t out_of_range_count;
} ChannelReport;

double adc_raw_to_voltage(uint16_t raw_value);
void adc_convert_voltages(ADCSample *samples, size_t count);
void adc_compute_channel_reports(const ADCSample *samples,
                                 size_t sample_count,
                                 ChannelReport reports[ADC_CHANNEL_COUNT]);

#endif