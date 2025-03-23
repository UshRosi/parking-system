# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Linker flags (add -lcurl for libcurl)
LDFLAGS = -lcurl

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Find all .cpp files in the source directory and its subdirectories
SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Convert .cpp filenames to .o filenames in obj/ directory while maintaining directory structure
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output executable
TARGET = $(BIN_DIR)/parking_system

# Default rule: Build the project
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile .cpp files into .o files, ensuring obj subdirectories exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Print detected source files (debugging)
print:
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"