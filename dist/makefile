CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Idist
LDFLAGS = -L./dist -Wl,-rpath=./dist
LDLIBS = -lwatchdog

# Change the name of c file
TARGET = user.out
SRC = user_file.c

.PHONY: clean debug run

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -g
debug: $(TARGET)

clean:
	rm -f $(TARGET)