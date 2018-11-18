CC = gcc
CFLAGS = -Wall -Wextra -std=c99

BIN = bin/OCR
SRC = src/OCR/*.c src/OCR/*/*.c

TOOLS_BIN = bin/Tools
TOOLS_SRC = src/OCR/NeuralNetwork/*.c src/OCR/Matrix.c src/Tools/*.c

GTK = `pkg-config --libs --cflags gtk+-3.0`
SDL = -lSDL2 -lSDL2_image
MATH = -lm

all: prebuild $(TOOLS_BIN)

prebuild:
	mkdir -p bin

$(BIN): $(SRC)
	$(CC) $(SRC) $(GTK) $(CFLAGS) -o $(BIN) $(GTK) $(SDL) $(MATH)

$(TOOLS_BIN): $(TOOLS_SRC)
	$(CC) $(TOOLS_SRC) $(CFLAGS) -o $(TOOLS_BIN) $(SDL) $(MATH)

clean:
	rm -rf $(BIN) $(TOOLS_BIN)
