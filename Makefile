# Makefile

# Compaler and flags
CXX = clang++
CXXFLAGS = -Weffc++ -Wconversion -Wsign-conversion -Wall -Wextra -Wpedantic -Werror 
CXXFLAGS += -std=c++20 -Iinclude 
CXXFLAGS +=  -include pch.hpp

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


release: CXXFLAGS += -O2
release: $(TARGET)

g: CXX = g++
# g: CXXFLAGS = -std=c++20 -Iinclude -include pch.hpp
g:all

# Debug
debug: CXXFLAGS += -fsanitize=address,undefined -O1 -DDEBUG -g
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build: 
	mkdir -p $(OBJ_DIR) 

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean debug all run release g
