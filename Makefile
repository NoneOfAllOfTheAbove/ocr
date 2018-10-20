CC = gcc
BIN = OCR
SRC = main.c Preprocessing.c DemoGUI.c NeuralNetwork.c Segmentation.c
CFLAGS = -Wall -Wextra -std=c99
GTK = $$(pkg-config --libs --cflags gtk+-3.0)

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(GTK) $(CFLAGS) -o $(BIN) -lSDL2 -lSDL2_image -lm

clean:
	rm -rf $(BIN)
