#include "adc.h"

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