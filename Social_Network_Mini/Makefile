# Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Isrc

SRC = $(wildcard src/*.cpp)
OUT = main.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(OUT)
