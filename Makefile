CC = gcc
BIN = OCR
SRC = main.c Image.c Segmentation.c
CFLAGS = -Wall -Wextra -std=c99
GTK = $$(pkg-config --libs --cflags gtk+-3.0)

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(GTK) $(CFLAGS) -o $(BIN) -lSDL2 -lSDL2_image

clean:
	rm -rf $(BIN)
