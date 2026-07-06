#include "stats.h"

#include <math.h>

double stats_mean(const double *values, size_t count) {
    double total = 0.0;

    for (size_t i = 0; i < count; i++) {
        total += values[i];
    }

    return total / count;
}

double stats_min(const double *values, size_t count) {
    double minimum = values[0];

    for (size_t i = 1; i < count; i++) {
        if (values[i] < minimum) {
            minimum = values[i];
        }
    }

    return minimum;
}

double stats_max(const double *values, size_t count) {
    double maximum = values[0];

    for (size_t i = 1; i < count; i++) {
        if (values[i] > maximum) {
            maximum = values[i];
        }
    }

    return maximum;
}

double stats_standard_deviation(const double *values, size_t count) {
    double mean = stats_mean(values, count);
    double total_squared_difference = 0.0;

    for (size_t i = 0; i < count; i++) {
        double difference = values[i] - mean;
        total_squared_difference += difference * difference;
    }

    return sqrt(total_squared_difference / count);
}