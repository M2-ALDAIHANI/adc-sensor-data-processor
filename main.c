#include "adc.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    ADCHeader header;
    ADCSample *samples;
    ChannelReport reports[ADC_CHANNEL_COUNT];
    SequenceGap gaps[20];
    size_t gap_count;

    if (argc != 2) {
        printf("Usage: %s adc_sensor_log.bin\n", argv[0]);
        return 1;
    }

    printf("Reading ADC file: %s\n", argv[1]);

    samples = io_read_adc_file(argv[1], &header);

    if (samples == NULL) {
        return 1;
    }

    adc_compute_channel_reports(samples, header.record_count, reports);

    gap_count = adc_check_sequence_gaps(samples,
                                        header.record_count,
                                        gaps,
                                        20);

    if (!io_write_results_file("results.txt",
                               &header,
                               reports,
                               gaps,
                               gap_count)) {
        free(samples);
        return 1;
    }

    if (!io_write_fault_report_file("fault_report.txt",
                                    samples,
                                    header.record_count)) {
        free(samples);
        return 1;
    }

    free(samples);

    printf("Analysis complete.\n");
    printf("Created results.txt and fault_report.txt.\n");

    return 0;
}