#ifndef STATS_H
#define STATS_H

#include <stddef.h>

double stats_mean(const double *values, size_t count);
double stats_min(const double *values, size_t count);
double stats_max(const double *values, size_t count);
double stats_standard_deviation(const double *values, size_t count);

#endif