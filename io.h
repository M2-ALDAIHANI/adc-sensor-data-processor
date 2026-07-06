#ifndef IO_H
#define IO_H

#include "adc.h"

int io_read_header(const char *filename, ADCHeader *header);

#endif