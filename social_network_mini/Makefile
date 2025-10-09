# Compaler and flags
CXX = g++
CXXFLAGS = -Werror -Wall -std=c++17 -Iinclude

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

# Debug
debug: CXXFLAGS += -O0 -DDEBUG
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

.PHONY: clean debug all run release