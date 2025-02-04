.PHONY: build run clean debug

PROJECT_NAME = cclox
BUILD_DIR = build

# Run the executable
run: build
	@./$(BUILD_DIR)/$(PROJECT_NAME) $(filter-out $@,$(MAKECMDGOALS))

# Build the project
build:
	@cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	@cmake --build $(BUILD_DIR) -- --no-print-directory -j$(nproc)

# Run with debug flags
debug:
	@cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DDEBUG_TRACE_EXECUTION=ON
	@cmake --build $(BUILD_DIR) -- --no-print-directory -j$(nproc)
	@./$(BUILD_DIR)/$(PROJECT_NAME) $(filter-out $@,$(MAKECMDGOALS))

# Clean the project
clean:
	@rm -rf $(BUILD_DIR)

# Prevent make from treating additional arguments as targets
%:
	@: