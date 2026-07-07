# ADC Sensor Data Processor

A C99 command-line application for analysing binary ADC sensor data collected from a 4-channel, 12-bit analogue-to-digital converter.

The program reads a binary sensor log, validates the file format, converts raw ADC readings into voltages, computes per-channel statistics, detects fault conditions, verifies sequence integrity, and generates structured output reports.


# Features

- Reads a binary ADC dataset (adc_sensor_log.bin)
- Validates the binary file header
- Converts raw ADC values to voltages
- Computes for each channel:
   - Mean voltage
   - Minimum voltage
   - Maximum voltage
   - Standard deviation
- Detects:
   - Overvoltage events
   - Undervoltage events
   - Sensor fault flags
   - Out-of-range flags
- Checks sequence numbers for missing records
- Generates:
   - results.txt
   - fault_report.txt


# Project Structure

main.c - program entry point
adc.c / adc.h - voltage conversion, statistics, fault detection and sequence checking
io.c / io.h - binary file reading and report generation
stats.c / stats.h - reusable statistical functions
CMakeLists.txt - build configuration
adc_sensor_log.bin - given dataset
results.txt - generated analysis report
fault_report.txt - detailed fault report


# Requirements

C compiler supporting C99 (GCC / MinGW)


# Build and Run (GCC)

Compile: gcc main.c adc.c io.c stats.c -o adc_program.exe -lm
Run: .\adc_program.exe adc_sensor_log.bin


# Output

The program generates :
- results.txt:
   - File header information
   - Per-channel statistics
   - Mean voltage
   - Minimum voltage
   - Maximum voltage
   - Standard deviation
   - Fault counts
   - Sequence integrity report

- fault_report.txt:
   - Timestamp of each fault
   - Channel number
   - Voltage value
   - Status flags
   - Fault type
   - Error Handling


# Summary

This project demonstrates binary file processing, modular C programming, dynamic memory allocation, pointer-based data access, statistical analysis, and robust error handling while analysing ADC sensor data.