#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>

void trace_memory_error(char* info);

void trace(char* info);

void trace_num(char* info, int num);

void new_line();

void print_line();

#endif