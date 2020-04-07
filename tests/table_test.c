#include "minunit.h"
#include <stdio.h>

#include "../table.h"
#include "../command.h"
#include "../line_utils.h"


int tests_run = 0;

static char* test_new_table()
{
    Table* table = new_table();
    mu_assert("table of wrong size",
        sizeof(table->pages) == TABLE_MAX_PAGES * sizeof(void*)
        );
    free_table(table);
    return 0;
}

static char* test_table_capacity()
{
    Table* table = new_table();
    InputBuffer* buffer = new_input_buffer();
    buffer->buffer = "insert 1 bob bob@example.com";
    buffer->input_length = 28;
    Statement statement;
    prepare_statement(buffer, &statement);
    for (uint32_t i = 0; i < TABLE_MAX_ROWS; i++)
    {
        mu_assert("table should be able to contain more rows",
            execute_insert(&statement, table) == EXECUTE_SUCCESS
            );
    }
    mu_assert("table able to contain more than expected!?",
        execute_insert(&statement, table) == EXECUTE_TABLE_FULL
        );
    free_table(table);
    return 0;
}

static char* all_tests()
{
    mu_run_test(test_new_table);
    mu_run_test(test_table_capacity);
    return 0;
}

int main(int argc, char const *argv[])
{
    char* result = all_tests();
    if (result != 0)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
