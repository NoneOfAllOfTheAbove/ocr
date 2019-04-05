# OCR



## Project

![Screenshot](https://raw.githubusercontent.com/NoneOfAllOfTheAbove/ocr/master/docs/screenshot.png)  

OCR stands for Optical Character Recognition software. As part of a student project, our objective is to make a program capable of extracting text from images. It must be written in the C language, rely on a neural network and be used through a GUI. To learn more, please take a look at [the book of specifications](https://github.com/NoneOfAllOfTheAbove/ocr/tree/master/docs/book-of-specifications.pdf).

## Usage

Dependencies: `SDL2`, `SDL2_image`, `GTK+ 3` and `Hunspell`.  

1. Clone this repository with `git clone git@github.com:NoneOfAllOfTheAbove/OCR.git`.
2. Compile the project by running the command `make` in the project folder.
3. Execute the program with `./bin/OCR`.

## Features

Currently implemented:
- Advanced preprocessing (efficient binarization, noise canceling, contrast enhancement)
- Detect paragraphs, lines, words and characters
- A pretrained neural network to recognize characters
- Simple GUI to load an image and export its extracted text
- Postprocessing step (spell check)
  
Features we are working on:
- De-skew
- Improve segmentation (export as HTML)
- Retrain the neural network

## Contributing

Refer to [CONTRIBUTING.md](https://github.com/NoneOfAllOfTheAbove/ocr/blob/master/CONTRIBUTING.md).