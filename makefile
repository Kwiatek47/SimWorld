COMPILER = g++
COMPILER_FLAGS = -std=c++17 -Wall -Wextra -g  # Dodano -g dla debugowania
SRC = $(wildcard *.cpp) $(wildcard Zwierzeta/*.cpp) $(wildcard Rosliny/*.cpp)
TARGET = main  # Poprawiono: spójność z `clean`

all: $(TARGET)

$(TARGET): $(SRC)
	$(COMPILER) $(COMPILER_FLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)