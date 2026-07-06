# ADC Sensor Data Processor

This program was built for analysing ADC sensor log data.
The program reads `adc_sensor_log.bin`, analyses ADC sensor data, and writes a complete report.

## Files

- `main.c` - program entry point and overall flow
- `adc.c / adc.h` - ADC structures, voltage conversion, statistics analysis, fault detection, sequence checking
- `io.c / io.h` - binary file reading and report writing
- `stats.c / stats.h` - reusable statistical functions
- `CMakeLists.txt` - CMake build file

## Build with GCC

gcc main.c adc.c io.c stats.c -o adc_program.exe -lm