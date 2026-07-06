#include "io.h"

#include <stdio.h>

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