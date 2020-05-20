#include "minunit.h"
#include <stdio.h>

#include "../table.h"
#include "../command.h"
#include "../line_utils.h"


int tests_run = 0;

static char* test_insert_and_retrieve_row()
{
    char actual[50];
    char expected[50];
    FILE * expected_file = fopen("./resources/test_insert_and_retrieve_row_output", "r");
    FILE * file = popen("./sqltoy ./test_db_file.db < ./resources/test_insert_and_retrieve_row_input", "r");
    for (int i = 0; i < 4; i++) {
        fgets(expected, sizeof(expected), expected_file);
        fgets(actual, sizeof(actual), file);
        printf("%d%s%s", i, actual, expected);
        mu_assert("inserts and retrieves a row", strcmp(expected, actual) == 0);
    }
    fclose(expected_file);
    fclose(file);
    return 0;
}

static char* all_tests()
{
    mu_run_test(test_insert_and_retrieve_row);
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
