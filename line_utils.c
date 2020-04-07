#include "line_utils.h"


InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = (char*)malloc(256);
    input_buffer->buffer_length = 256;
    input_buffer->input_length = 0;

    return input_buffer;
}

void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

void print_prompt()
{
    printf("db > ");
}

void read_input(InputBuffer* input_buffer)
{
    int status = getLine(input_buffer);

    if (status != OK)
    {
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = strlen(input_buffer->buffer);
}

// function adapted from here:
// https://stackoverflow.com/questions/4023895/how-do-i-read-a-string-entered-by-the-user-in-c/4023921#4023921
int getLine(InputBuffer* buff)
{
    if (fgets(buff->buffer, buff->buffer_length, stdin) == NULL)
    {
        return NO_INPUT;
    }
    
    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff->buffer[strlen(buff->buffer)-1] != '\n') {
        int extra = 0;
        int ch;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff->buffer[strlen(buff->buffer)-1] = '\0';
    return OK;
}

void print_row(Row* row)
{
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}