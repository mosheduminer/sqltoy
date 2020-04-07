default:
	make test && ./test && make build

build: main.c command.c line_utils.c
	gcc -o sqltoy main.c command.c line_utils.c table.c -Werror -Wall

test: tests/table_test.c
	gcc -o test tests/table_test.c table.c line_utils.c command.c -Werror -Wall