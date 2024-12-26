TARGET = ./main
CXX = g++

SRC_DIR = ./source/
INCLUDE_DIR = ./include/
BIN_DIR = ./bin/

CXXFLAGS =-g -I$(INCLUDE_DIR) -Wall -pedantic 

SRC = $(wildcard $(SRC_DIR)*.cpp)

OBJ = $(patsubst $(SRC_DIR)%.cpp, $(BIN_DIR)%.o, $(SRC))

all : create_bin_dir $(TARGET)

run: clean all
	$(TARGET)

$(BIN_DIR)%.o : $(SRC_DIR)%.cpp $(INCLUDE_DIR)*.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

create_bin_dir :
	@mkdir -p $(BIN_DIR)

clean:
	@rm -f $(TARGET)
	@rm -rf $(BIN_DIR)