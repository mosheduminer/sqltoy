#ifndef LINE_UTILS
#define LINE_UTILS

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

typedef struct
{
    char* buffer;
    size_t buffer_length;
    int input_length;
} InputBuffer;

InputBuffer* new_input_buffer();

void close_input_buffer(InputBuffer* input_buffer);

void print_prompt();

void read_input(InputBuffer* input_buffer);

int getLine(InputBuffer* buff);

void print_row(Row* row);

#endif