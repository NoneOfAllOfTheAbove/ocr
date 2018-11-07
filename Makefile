CC = gcc
BIN = OCR
SRC = src/*.c src/*/*.c
CFLAGS = -Wall -Wextra -std=c99
GTK = $$(pkg-config --libs --cflags gtk+-3.0)

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(GTK) $(CFLAGS) -o $(BIN) -export-dynamic -lSDL2 -lSDL2_image -lm

clean:
	rm -rf $(BIN)
