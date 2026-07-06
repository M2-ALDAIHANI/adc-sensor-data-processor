#ifndef IO_H
#define IO_H

#include "adc.h"

int io_read_header(const char *filename, ADCHeader *header);
ADCSample *io_read_adc_file(const char *filename, ADCHeader *header);

int io_write_results_file(const char *filename,
                          const ADCHeader *header,
                          const ChannelReport reports[ADC_CHANNEL_COUNT],
                          const SequenceGap *gaps,
                          size_t gap_count);

int io_write_fault_report_file(const char *filename,
                               const ADCSample *samples,
                               size_t sample_count);

#endif