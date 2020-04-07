#include "line_utils.h"
#include "table.h"

typedef enum MetaCommandResult {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum StatementType {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;


typedef struct Statement {
    StatementType type;
    Row row_to_insert;
} Statement;

typedef enum ExecuteResult {
    EXECUTE_TABLE_FULL,
    EXECUTE_SUCCESS
} ExecuteResult;


MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

ExecuteResult execute_insert(Statement* statement, Table* table);

ExecuteResult execute_select(Statement* statement, Table* table);

ExecuteResult execute_statement(Statement* statement, Table* table);
