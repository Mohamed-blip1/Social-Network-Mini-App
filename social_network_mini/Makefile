# Compaler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++20 -Iinclude

# Project name
TARGET= main

# Directories
SRC_DIR = src
OBJ_DIR = build

# Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default
all: release

release: CXXFLAGS += -O3
release: $(TARGET)

g: CXX = g++

# Debug
debug: CXXFLAGS += -fsanitize=address,undefined -O1 -DDEBUG -g
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean debug all run release g