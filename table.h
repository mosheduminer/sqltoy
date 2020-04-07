#ifndef TABLE
#define TABLE

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
// posix only
#include <unistd.h>


#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct Row
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

#define ID_SIZE size_of_attribute(Row, id)
#define USERNAME_SIZE size_of_attribute(Row, username)
#define EMAIL_SIZE size_of_attribute(Row, email)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)
#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)


void serialize_row(Row* source, void* destination);

void deserialize_row(void* source, Row* destination);


#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

typedef struct Pager
{
    int file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct Table
{
    uint32_t num_rows;
    Pager* pager;
} Table;

void* row_slot(Table* table, uint32_t row_num);

Table* db_open(const char* file_name);

void db_close(Table* table);

void* get_page(Pager* pager, uint32_t page_num);

Pager* pager_open(const char* file_name);

void pager_flush(Pager* pager, uint32_t page_num, uint32_t size);

#endif