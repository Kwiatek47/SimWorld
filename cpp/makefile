COMPILER = g++
COMPILER_FLAGS = -std=c++17 -Wall -Wextra -g  
SRC = $(wildcard *.cpp) $(wildcard Zwierzeta/*.cpp) $(wildcard Rosliny/*.cpp)
TARGET = main 

all: $(TARGET)

$(TARGET): $(SRC)
	$(COMPILER) $(COMPILER_FLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)