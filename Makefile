CC = g++
OUT_DIR = build
CFLAGS = -c -Wall -Werror -Wpedantic -Wunreachable-code -Wextra -g -std=c++17 -O2
TFLAGS = -D TEST
INC = -I includes

all : algo

algo : main.o algo.o # Add other .o files here
		$(CC) main.o algo.o -o algo
		@mkdir -p $(OUT_DIR)
		@mv *.o $(OUT_DIR)
		@mv algo $(OUT_DIR)

main.o : src/main.cpp
			$(CC) $(CFLAGS) src/main.cpp $(OUTPUT) $(INC)

algo.o : src/algo.cpp
			$(CC) $(CFLAGS) src/algo.cpp $(OUTPUT) $(INC)

test:
			./scripts/test

clean : 
			rm -rf $(OUT_DIR)
			
