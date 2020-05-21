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
    for (int i = 0; i < 4; i++)
    {
        fgets(expected, sizeof(expected), expected_file);
        fgets(actual, sizeof(actual), file);
        mu_assert("inserts and retrieves a row", strcmp(expected, actual) == 0);
    }
    fclose(expected_file);
    fclose(file);
    remove("./test_db_file.db");
    return 0;
}

static char* test_table_full()
{
    remove("./resources/output_dump");
    FILE * file = popen("./sqltoy ./test_db_file.db >> ./resources/output_dump", "w");
    for (int i = 0; i <= 1300; i++)
    {
        fprintf(file, "insert %d user%d person%d@example.com\n", i, i, i);
    }
    fprintf(file, ".exit");
    fclose(file);
    FILE * expected_file = fopen("./resources/output_dump", "r");
    char line[50];
    int i = 0;
    while (fgets(line, sizeof(line), expected_file) && i < 1300)
    {
        i++;
    }
    fclose(expected_file);
    mu_assert("prints error message when table is full",
                strcmp("db > Error: Table full.\n", line) == 0);
    remove("./resources/output_dump");
    remove("./test_db_file.db");
    return 0;
}

static char* test_too_long_input()
{
    char too_long_email[256], too_long_username[33];
    memset(too_long_email, 'a', 256);
    memset(too_long_username, 'a', 33);
    FILE * file = popen("./sqltoy ./test_db_file.db > ./resources/output_dump", "w");
    fprintf(file, "insert 1 %s %s\n", too_long_username, too_long_email);
    fclose(file);
    FILE * expected_file = fopen("./resources/output_dump", "r");
    char line[50];
    fgets(line, sizeof(line), expected_file);
    printf("%s", too_long_email);
    mu_assert("prints error message if strings are too long",
                    strcmp(line, "String is too long.\n") == 0);
    return 0;
}

static char* all_tests()
{
    mu_run_test(test_insert_and_retrieve_row);
    mu_run_test(test_table_full);
    mu_run_test(test_too_long_input);
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
