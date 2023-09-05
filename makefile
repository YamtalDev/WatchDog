# Name of file
NAME = watch_dog

# The compiler : gcc for C program :
CC = gcc

# Compiler flags :
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -lpthread -lrt -fPIC -c

# Valgrind
VALGRIND = valgrind --leak-check=yes --track-origins=yes -s

# Debugtest
DEBUG = gdb -tui

#Remove
RM = rm -rf

# Path to header
PATH_TO_HEADER = -Iinclude/

# User main file
USER_MAIN = test/$(NAME)_test.c

# main file
MAIN = src/wd_$(NAME).c

# User o main file
O_USER_MAIN = lib/$(NAME)_test.o

# Main file
O_MAIN = lib/wd_$(NAME).o

# Shared Lib names
SO_NAME = dist/libwatchdog.so

# Shared lib path
PATH_TO_SO = dist/

# Source files, headers, Object files
SRC = src/$(NAME).c
O_SRC = lib/$(NAME).o
HEADER = include/$(NAME).h

EXTERNAL_O_SRC = lib/wd_heap.o
EXTERNAL_SRC = src/wd_heap.c
EXTERNAL_HEADER = include/wd_heap.h

EXTERNAL_O_SRC_1 = lib/wd_heap_pq.o
EXTERNAL_SRC_1 = src/wd_heap_pq.c
EXTERNAL_HEADER_1 = include/wd_heap_pq.h

EXTERNAL_O_SRC_2 = lib/wd_heap_scheduler.o
EXTERNAL_SRC_2 = src/wd_heap_scheduler.c
EXTERNAL_HEADER_2 = include/wd_heap_scheduler.h

EXTERNAL_O_SRC_3 = lib/wd_vector.o
EXTERNAL_SRC_3 = src/wd_vector.c
EXTERNAL_HEADER_3 = include/wd_vector.h

EXTERNAL_O_SRC_4 = lib/wd_task.o
EXTERNAL_SRC_4 = src/wd_task.c
EXTERNAL_HEADER_4 = include/wd_task.h

EXTERNAL_O_SRC_5 = lib/wd_unique_identifier.o
EXTERNAL_SRC_5 = src/wd_unique_identifier.c
EXTERNAL_HEADER_5 = include/wd_unique_identifier.h

EXTERNAL_O_SRC_6 = lib/wd_internal_lib.o
EXTERNAL_SRC_6 = src/wd_internal_lib.c
EXTERNAL_HEADER_6 = include/wd_internal_lib.h

# The build target executable
TARGET = dist/watchdog.out

# The usertest build target executable
TEST_TARGET = test/watchdog_test.out

# C Files of the project
C_FILES = $(SRC) $(EXTERNAL_SRC) $(EXTERNAL_SRC_1) $(EXTERNAL_SRC_2) $(EXTERNAL_SRC_3) $(EXTERNAL_SRC_4) $(EXTERNAL_SRC_5) $(EXTERNAL_SRC_6)

# O Files of the project
O_FILES = $(O_SRC) $(EXTERNAL_O_SRC) $(EXTERNAL_O_SRC_1) $(EXTERNAL_O_SRC_2) $(EXTERNAL_O_SRC_3) $(EXTERNAL_O_SRC_4) $(EXTERNAL_O_SRC_5) $(EXTERNAL_O_SRC_6)

# List of all headers
HEADERS = $(HEADER) $(EXTERNAL_HEADER) $(EXTERNAL_HEADER_1) $(EXTERNAL_HEADER_2) $(EXTERNAL_HEADER_3) $(EXTERNAL_HEADER_4) $(EXTERNAL_HEADER_5) $(EXTERNAL_HEADER_6)

.PHONY : run link_test vlg release debug clean

#******************************************************************************

release : CFLAGS += -DNDEBUG -O3
release : clean $(SO_NAME)

#******************************************************************************

debug : CFLAGS += -DDEBUG_ON -g
debug : clean link_test
	clear
	$(DEBUG) $(TEST_TARGET)

#******************************************************************************

run : release link_test
	clear
	$(TEST_TARGET)

#******************************************************************************

$(SO_NAME) : $(O_FILES) $(HEADERS)
	$(CC) $(PATH_TO_HEADER) -shared -o $(SO_NAME) $(O_FILES)
	$(CC) $(PATH_TO_HEADER) -L$(PATH_TO_SO) -Wl,-rpath=$(PATH_TO_SO) -Wall $(MAIN) $(O_FILES) -o $(TARGET) -lwatchdog

#******************************************************************************

link_test : $(USER_MAIN) $(SO_NAME)
	$(CC) $(CFLAGS) $(PATH_TO_HEADER) -c $(USER_MAIN) -o $(O_USER_MAIN)
	$(CC) $(PATH_TO_HEADER) -L$(PATH_TO_SO) -Wl,-rpath=$(PATH_TO_SO) $(O_USER_MAIN) -o $(TEST_TARGET) -lwatchdog


#******************************************************************************

vlg : link_test
	clear
	$(VALGRIND) $(TEST_TARGET)

#******************************************************************************

$(O_SRC) : $(SRC) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)

$(EXTERNAL_O_SRC) : $(EXTERNAL_SRC) $(EXTERNAL_HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC) -o $(EXTERNAL_O_SRC)

$(EXTERNAL_O_SRC_1) : $(EXTERNAL_SRC_1) $(EXTERNAL_HEADER_1)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC_1) -o $(EXTERNAL_O_SRC_1)

$(EXTERNAL_O_SRC_2) : $(EXTERNAL_SRC_2) $(EXTERNAL_HEADER_2)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC_2) -o $(EXTERNAL_O_SRC_2)

$(EXTERNAL_O_SRC_3) : $(EXTERNAL_SRC_3) $(EXTERNAL_HEADER_3)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC_3) -o $(EXTERNAL_O_SRC_3)

$(EXTERNAL_O_SRC_4) : $(EXTERNAL_SRC_4) $(EXTERNAL_HEADER_4)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC_4) -o $(EXTERNAL_O_SRC_4)

$(EXTERNAL_O_SRC_5) : $(EXTERNAL_SRC_5) $(EXTERNAL_HEADER_5)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC_5) -o $(EXTERNAL_O_SRC_5)

$(EXTERNAL_O_SRC_6) : $(EXTERNAL_SRC_6) $(EXTERNAL_HEADER_6)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC_6) -o $(EXTERNAL_O_SRC_6)


#******************************************************************************

clean :
	clear
	$(RM) $(TARGET) $(O_FILES) $(SO_NAME) $(TEST_TARGET)

#******************************************************************************