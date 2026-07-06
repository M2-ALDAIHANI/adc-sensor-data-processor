#include "io.h"

#include <stdio.h>
#include <stdlib.h>

int io_read_header(const char *filename, ADCHeader *header) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error: could not open input file '%s'.\n", filename);
        return 0;
    }

    if (fread(header, sizeof(ADCHeader), 1, file) != 1) {
        printf("Error: could not read the 24-byte file header.\n");
        fclose(file);
        return 0;
    }

    fclose(file);

    if (header->magic != ADC_MAGIC_NUMBER) {
        printf("Error: invalid magic number. Expected 0x%08X, got 0x%08X.\n",
               ADC_MAGIC_NUMBER, header->magic);
        return 0;
    }

    if (header->version != ADC_EXPECTED_VERSION) {
        printf("Error: unsupported file version.\n");
        return 0;
    }

    if (header->channel_count != ADC_CHANNEL_COUNT) {
        printf("Error: unexpected channel count.\n");
        return 0;
    }

    if (header->sample_rate_hz != ADC_SAMPLE_RATE_HZ) {
        printf("Error: unexpected sample rate.\n");
        return 0;
    }

    return 1;
}

ADCSample *io_read_adc_file(const char *filename, ADCHeader *header) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error: could not open input file '%s'.\n", filename);
        return NULL;
    }

    if (fread(header, sizeof(ADCHeader), 1, file) != 1) {
        printf("Error: could not read the 24-byte file header.\n");
        fclose(file);
        return NULL;
    }

    if (header->magic != ADC_MAGIC_NUMBER) {
        printf("Error: invalid magic number. Expected 0x%08X, got 0x%08X.\n",
               ADC_MAGIC_NUMBER, header->magic);
        fclose(file);
        return NULL;
    }

    ADCBinaryRecord *binary_records =
            malloc(header->record_count * sizeof(ADCBinaryRecord));

    if (binary_records == NULL) {
        printf("Error: memory allocation failed for binary records.\n");
        fclose(file);
        return NULL;
    }

    size_t records_read = fread(binary_records,
                                sizeof(ADCBinaryRecord),
                                header->record_count,
                                file);

    fclose(file);

    if (records_read != header->record_count) {
        printf("Error: file ended early. Expected %u records, read %zu.\n",
               header->record_count, records_read);
        free(binary_records);
        return NULL;
    }

    ADCSample *samples = malloc(header->record_count * sizeof(ADCSample));

    if (samples == NULL) {
        printf("Error: memory allocation failed for samples.\n");
        free(binary_records);
        return NULL;
    }

    for (size_t i = 0; i < header->record_count; i++) {
        samples[i].timestamp = binary_records[i].timestamp;
        samples[i].channel_id = binary_records[i].channel_id;
        samples[i].raw_value = binary_records[i].raw_value;
        samples[i].voltage = 0.0;
        samples[i].temperature = binary_records[i].temperature;
        samples[i].status_flags = binary_records[i].status_flags;
        samples[i].sequence_number = binary_records[i].sequence_number;
    }

    free(binary_records);
    return samples;
}