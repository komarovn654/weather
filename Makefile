TARGET = weather.out
FLAGS = -Wall -Wextra -Wpedantic -std=c11
SRC_DIR = src
INC_DIR = include
STATIC_LIB = -lcurl -ljson-c

all: 
	gcc -o $(TARGET) $(SRC_DIR)/*.c -I $(INC_DIR) $(FLAGS) $(STATIC_LIB)

.PHONY: clean
clean:
	-rm $(TARGET)	