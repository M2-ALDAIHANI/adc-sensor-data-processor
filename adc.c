#include "adc.h"
#include "stats.h"

#include <stdlib.h>

double adc_raw_to_voltage(uint16_t raw_value) {
    return (raw_value / ADC_MAX_RAW_VALUE) * ADC_REFERENCE_VOLTAGE;
}

void adc_convert_voltages(ADCSample *samples, size_t count) {
    ADCSample *current = samples;
    ADCSample *end = samples + count;

    while (current < end) {
        current->voltage = adc_raw_to_voltage(current->raw_value);
        current++;
    }
}

void adc_compute_channel_reports(const ADCSample *samples,
                                 size_t sample_count,
                                 ChannelReport reports[ADC_CHANNEL_COUNT]) {
    for (size_t channel = 0; channel < ADC_CHANNEL_COUNT; channel++) {
        size_t count = 0;

        for (size_t i = 0; i < sample_count; i++) {
            if (samples[i].channel_id == channel) {
                count++;
            }
        }

        double *voltages = malloc(count * sizeof(double));

        if (voltages == NULL) {
            reports[channel].channel_id = (uint8_t)channel;
            reports[channel].sample_count = 0;
            reports[channel].mean_voltage = 0.0;
            reports[channel].min_voltage = 0.0;
            reports[channel].max_voltage = 0.0;
            reports[channel].standard_deviation = 0.0;
            reports[channel].overvoltage_count = 0;
            reports[channel].undervoltage_count = 0;
            reports[channel].sensor_fault_count = 0;
            reports[channel].out_of_range_count = 0;
            continue;
        }

        size_t voltage_index = 0;

        for (size_t i = 0; i < sample_count; i++) {
            if (samples[i].channel_id == channel) {
                voltages[voltage_index] = samples[i].voltage;
                voltage_index++;
            }
        }

        reports[channel].channel_id = (uint8_t)channel;
        reports[channel].sample_count = count;
        reports[channel].mean_voltage = stats_mean(voltages, count);
        reports[channel].min_voltage = stats_min(voltages, count);
        reports[channel].max_voltage = stats_max(voltages, count);
        reports[channel].standard_deviation = stats_standard_deviation(voltages, count);
        reports[channel].overvoltage_count = 0;
        reports[channel].undervoltage_count = 0;
        reports[channel].sensor_fault_count = 0;
        reports[channel].out_of_range_count = 0;

        free(voltages);
    }
}