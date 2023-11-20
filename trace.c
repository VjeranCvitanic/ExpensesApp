#include "trace.h"

void trace_memory_error(char* info)
{
    print_line();
    printf("Memory error: out of memory\nCan't allocate memory");
    printf("Additional info: %s", info);
    print_line();
}

void trace(char* info)
{
    print_line();
    printf("Trace: info: %s", info);
    print_line();
}

void trace_num(char* info, int num)
{
    print_line();
    printf("Trace: info: %s %d", info, num);
    print_line();
}

void new_line()
{
    printf("\n");
}

void print_line()
{
    new_line();
    printf("-------------------------------------------------------");
    new_line();
}
