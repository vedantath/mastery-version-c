# Compiler and flags
CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -DDEBUG

# Source and object files
SRC = main.c reader.c calculator.c
OBJ = main.o reader.o calculator.o
EXEC = mini_ci
REFERENCE_EXEC = mini_ci_reference
OUTPUT_DIR = outputs

# Default target (the executable)
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Pattern rule for compiling .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug target (compiles with debug flags)
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXEC)

# Tests target depends on the executable
tests: $(EXEC)
	@for testfile in testcases/*; do \
		echo "Running $$testfile..."; \
		./$(EXEC) $$testfile; \
	done

# Check target compares output with mini_ci_reference
check: $(EXEC)
	@mkdir -p $(OUTPUT_DIR)
	@for testfile in testcases/*; do \
		base_name=$$(basename $$testfile); \
		./$(EXEC) $$testfile > $(OUTPUT_DIR)/$$base_name.out; \
		./$(REFERENCE_EXEC) $$testfile > $(OUTPUT_DIR)/$$base_name.ref; \
		if diff $(OUTPUT_DIR)/$$base_name.out $(OUTPUT_DIR)/$$base_name.ref > /dev/null; then \
			echo "✅ PASSED $$testfile"; \
		else \
			echo "❌ FAILED $$testfile"; \
			echo "Diff:"; \
			diff $(OUTPUT_DIR)/$$base_name.out $(OUTPUT_DIR)/$$base_name.ref; \
		fi; \
	done


# Clean target to remove compiled files
clean:
	rm -f $(EXEC) $(OBJ)
