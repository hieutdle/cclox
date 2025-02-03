.PHONY: build# Project settings
PROJECT_NAME = cclox
BUILD_DIR = build

# Run the executable
run: build
	@./$(BUILD_DIR)/$(PROJECT_NAME)

# Build the project
build:
	@cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	@cmake --build $(BUILD_DIR) -- --no-print-directory -j$(nproc)

# Clean the project
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all build run clean