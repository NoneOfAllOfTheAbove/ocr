CC = gcc
CFLAGS = -Wall -Wextra -std=c99

BIN = bin/OCR
SRC = src/main.c src/Matrix.c src/Stack.c src/*/*.c

TOOLS_BIN = bin/Tools
TOOLS_SRC = src/NeuralNetwork/*.c src/Matrix.c src/Preprocessing/*.c src/tools.c

GTK = `pkg-config --libs --cflags gtk+-3.0`
SDL = -lSDL2 -lSDL2_image
MATH = -lm

all: prebuild $(BIN) $(TOOLS_BIN)

prebuild:
	mkdir -p bin

$(BIN): $(SRC)
	$(CC) $(SRC) $(GTK) $(CFLAGS) -o $(BIN) $(GTK) $(SDL) $(MATH)

$(TOOLS_BIN): $(TOOLS_SRC)
	$(CC) $(TOOLS_SRC) $(CFLAGS) -o $(TOOLS_BIN) $(SDL) $(MATH)

clean:
	rm -rf $(BIN) $(TOOLS_BIN)
