# Compiler and flags
CC=gcc
CFLAGS=-Wall -Werror -g
LDFLAGS=-lm
OBJS=main.o
TARGET=mtll
TEST_TARGET=test.sh

.PHONY: all clean tests run_tests

# Build the target executable
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@  # Link object files to create the executable

# Compile .c files into .o files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Run tests using the test script
tests:
	echo "Compiling tests..."
	chmod u+x test.sh
	./test.sh

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET) *.o
