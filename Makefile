CXX = g++
CXXFLAGS = -g -Wall -Werror -pedantic --std=c++2a 

SRC = src
BIN = bin
TEST = test
TARGET = file-synchronization
 
.PHONY: build
build: $(BIN)/$(TARGET)

.PHONY: run
run: $(BIN)/$(TARGET)
	$(BIN)/$(TARGET) test/source test/replica -l log.log -i 5

.PHONY: debug
debug: $(BIN)/$(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(BIN)/$(TARGET) -s $(TEST)

.PHONY: clean
clean:
	rm -rf $(BIN)

$(BIN)/$(TARGET): $(BIN)/main.o $(BIN)/logger.o $(BIN)/synchronizer.o
	@mkdir -p $(BIN)
	$(CXX) $(CXXLINKFLAGS) $^ -o $@

$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/main.o: $(SRC)/main.cpp $(SRC)/synchronizer.hpp
$(BIN)/logger.o: $(SRC)/logger.cpp $(SRC)/logger.hpp
$(BIN)/synchronizer.o: $(SRC)/synchronizer.cpp $(SRC)/synchronizer.hpp $(SRC)/logger.hpp 

