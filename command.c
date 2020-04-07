#include "command.h"


MetaCommandResult do_meta_command(InputBuffer* input_buffer)
{
    if (strncmp(input_buffer->buffer, ".exit", 6) == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    PrepareResult result;
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(input_buffer->buffer, "insert %d %s %s",
                &(statement->row_to_insert.id),
                statement->row_to_insert.username,
                statement->row_to_insert.email);
        if (args_assigned < 3)
        {
            return PREPARE_SYNTAX_ERROR;
        }
        result = PREPARE_SUCCESS;
    }
    else if (strcmp(input_buffer->buffer, "select") == 0)
    {
        statement->type = STATEMENT_SELECT;
        result = PREPARE_SUCCESS;
    }
    else
    {
        result = PREPARE_UNRECOGNIZED_STATEMENT;
    }
    return result;
}

ExecuteResult execute_insert(Statement* statement, Table* table)
{
    if (table->num_rows >=TABLE_MAX_ROWS)
    {
        return EXECUTE_TABLE_FULL;
    }

    Row* row_to_insert = &(statement->row_to_insert);

    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table)
{
    Row row;
    for (uint32_t i = 0; i < table->num_rows; i++)
    {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table)
{
    ExecuteResult result;
    switch (statement->type)
    {
    case STATEMENT_INSERT:
        result = execute_insert(statement, table);
        break;
    case STATEMENT_SELECT:
        result = execute_select(statement, table);
        break;
    }
    return result;
}