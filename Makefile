CXX = g++
CXXFLAGS = -Wall -Iinclude
SRC_DIR = src
BIN_DIR = bin

all: $(BIN_DIR)/demo

$(BIN_DIR)/demo: $(SRC_DIR)/main.cpp $(SRC_DIR)/malloc_custom.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BIN_DIR)