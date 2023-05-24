CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O0 -g --coverage

TARGET = qsort
SRCS = qsort.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean test coverage

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.gcov *.gcda *.gcno *.info html -r

test: $(TARGET)
	@for i in $$(seq 1 7); do \
		./$(TARGET) < test$$i.txt; \
	done

coverage: $(TARGET)
	lcov --rc lcov_branch_coverage=1 -c -d . -o coverage.info
	genhtml --branch-coverage coverage.info -o html
