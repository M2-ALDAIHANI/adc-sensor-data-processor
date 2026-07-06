#ifndef IO_H
#define IO_H

#include "adc.h"

int io_read_header(const char *filename, ADCHeader *header);
ADCSample *io_read_adc_file(const char *filename, ADCHeader *header);

#endif